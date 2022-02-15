#!/usr/bin/env python
# -*- coding: utf-8 -*-

import gym
from gym.spaces import Discrete, Box
import numpy as np
import random

import ray
from ray import tune
from ray.rllib.agents import ppo
from ray.rllib.env.env_context import EnvContext
from ray.rllib.models import ModelCatalog
from ray.rllib.models.torch.torch_modelv2 import TorchModelV2
from ray.rllib.models.torch.fcnet import FullyConnectedNetwork as TorchFC
from ray.rllib.utils.framework import try_import_torch
from ray.rllib.utils.test_utils import check_learning_achieved
from ray.tune.logger import pretty_print

from WorldGenerateEnvironment import WorldGenerateEnvironment as MyEnv

torch, nn = try_import_torch()

class RayEnv(MyEnv):
    def __init__(self, config: EnvContext):
        MyEnv.__init__(self)
        return

class SimpleCorridor(gym.Env):
    """Example of a custom env in which you have to walk down a corridor.

    You can configure the length of the corridor via the env config."""

    def __init__(self, config: EnvContext):
        self.end_pos = config["corridor_length"]
        self.cur_pos = 0
        self.action_space = Discrete(2)
        self.observation_space = Box(0.0, self.end_pos, shape=(1,), dtype=np.float32)
        self.seed(config.worker_index * config.num_workers)

    def reset(self):
        self.cur_pos = 0
        return [self.cur_pos]

    def step(self, action):
        assert action in [0, 1], action
        if action == 0 and self.cur_pos > 0:
            self.cur_pos -= 1
        elif action == 1:
            self.cur_pos += 1
        done = self.cur_pos >= self.end_pos
        return [self.cur_pos], random.random() * 2 if done else -0.1, done, {}

    def seed(self, seed=None):
        random.seed(seed)


class TorchCustomModel(TorchModelV2, nn.Module):
    """Example of a PyTorch custom model that just delegates to a fc-net."""

    def __init__(self, obs_space, action_space, num_outputs, model_config, name):
        TorchModelV2.__init__(
            self, obs_space, action_space, num_outputs, model_config, name
        )
        nn.Module.__init__(self)

        self.torch_sub_model = TorchFC(
            obs_space, action_space, num_outputs, model_config, name
        )

    def forward(self, input_dict, state, seq_lens):
        input_dict["obs"] = input_dict["obs"].float()
        fc_out, _ = self.torch_sub_model(input_dict, state, seq_lens)
        return fc_out, []

    def value_function(self):
        return torch.reshape(self.torch_sub_model.value_function(), [-1])


class RLlibTrainer(object):
    def __init__(self):
        self.run = "PPO"
        self.as_test = True
        self.config = {
            "env": RayEnv,
            #  "env": SimpleCorridor,
            #  "env_config": {
            #      "corridor_length": 5,
            #  },
            "num_gpus": 1,
            "model": {
                "custom_model": "my_model",
                "vf_share_layers": True,
            },
            "num_workers": 1,
            "framework": "torch",
            "evaluation_num_workers": 1,
            "evaluation_config": {
                "render_env": True,
            },
        }
        self.stop = {
            "training_iteration": 50,
            "timesteps_total": 100000,
            "episode_reward_mean": 0.1,
        }
        return

    def initRay(self):
        ray.init(local_mode=False)
        ModelCatalog.register_custom_model("my_model", TorchCustomModel)
        return True

    def manualTrain(self):
        if self.run != "PPO":
            print("[ERROR][RLlibTrainer::manualTrain]")
            print("manual train only support PPO method!")
            return False

        ppo_config = ppo.DEFAULT_CONFIG.copy()
        ppo_config.update(self.config)
        ppo_config["lr"] = 1e-3

        trainer = ppo.PPOTrainer(config=ppo_config, env=self.config["env"])

        for _ in range(self.stop["training_iteration"]):
            result = trainer.train()
            print(pretty_print(result))
            if (result["timesteps_total"] >= self.stop["timesteps_total"] or
                result["episode_reward_mean"] >= self.stop["episode_reward_mean"]):
                break

        trainer.evaluate()
        return True

    def tuneTrain(self):
        results = tune.run(self.run, config=self.config, stop=self.stop)

        if self.as_test:
            check_learning_achieved(results, self.stop["episode_reward_mean"])
        return True

    def closeRay(self):
        ray.shutdown()
        return True

def demo_manual_train():
    rllib_trainer = RLlibTrainer()
    rllib_trainer.initRay()
    rllib_trainer.manualTrain()
    rllib_trainer.closeRay()
    return True

def demo_tune_train():
    rllib_trainer = RLlibTrainer()
    rllib_trainer.initRay()
    rllib_trainer.tuneTrain()
    rllib_trainer.closeRay()
    return True

if __name__ == "__main__":
    demo_manual_train()

