#!/usr/bin/env python
# -*- coding: utf-8 -*-

import ray
from ray import tune
from ray.rllib.agents import ppo
from ray.rllib.env.env_context import EnvContext
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

class RayModel(TorchModelV2, nn.Module):
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
            "env_config": {
                "test": True,
            },
            "model": {
                "custom_model": RayModel,
                "vf_share_layers": True,
            },
            "framework": "torch",
            "num_gpus": 1,
            "num_workers": 1,
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
        ray.init(address="auto")
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
    demo_tune_train()

