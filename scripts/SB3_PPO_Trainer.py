#!/usr/bin/env python
# -*- coding: utf-8 -*-

import os
import gym

from torch.utils.tensorboard import SummaryWriter

from stable_baselines3 import PPO as Method
from stable_baselines3.common.env_checker import check_env
from stable_baselines3.common.env_util import make_vec_env
from stable_baselines3.common.vec_env import DummyVecEnv, SubprocVecEnv, VecNormalize, VecFrameStack

from WorldGenerateEnvironment import WorldGenerateEnvironment as CustomEnv

class RL_Trainer:
    def __init__(self):
        self.platform = "SB3"
        self.method = "PPO"
        self.env_name = "CustomEnv"
        self.train_mode = True
        self.num_cpu = 6
        self.train_episode = -1
        self.timesteps_per_episode = 50000
        self.verbose = 1
        self.model_save_path = "./trained_model/"
        self.log_dir = "./log/"

        self.policy = "CnnPolicy"
        self.global_seed = 0
        self.lr = 1e-5
        self.ent_coef = 0.01

        self.env = None
        self.start_episode = 0
        return

    def updatePath(self):
        if self.model_save_path[-1] != "/":
            self.model_save_path += "/"
        self.model_save_path += self.platform + "/" + self.method + "/"

        if self.log_dir[-1] != "/":
            self.log_dir += "/"
        self.log_dir += self.platform + "/" + self.method + "/"
        return True

    def setGlobalSeed(self, seed=0):
        self.global_seed = seed
        return True

    def makeEnv(self, rank, seed=0):
        def _init():
            env = CustomEnv()
            env.setWriter(SummaryWriter(self.log_dir + "Reward/"), seed)
            return env
        self.setGlobalSeed(seed)
        return _init

    def makeFramestackEnv(self, rank, seed=0):
        def _init():
            env = CustomEnv()
            env.setWriter(SummaryWriter(self.log_dir + "Reward/"), seed)
            env = DummyVecEnv([lambda : env])
            env = VecFrameStack(env, n_stack=4)
            return env
        self.setGlobalSeed(seed)
        return _init

    def loadGymEnv(self):
        self.env = None

        if self.train_mode:
            self.env = make_vec_env(self.env_name, n_envs=4)
        else:
            self.env = make_vec_env(self.env_name, n_envs=1)

        #  check_env(env)
        return True

    def loadCostumEnv(self, rank=10):
        self.env = None

        if self.train_mode:
            if self.policy == "CnnLnLstmPolicy" or self.policy == "CnnLstmPolicy":
                self.env = SubprocVecEnv([self.makeEnv(rank, i) for i in range(self.num_cpu)])
            elif self.policy == "CnnPolicy":
                self.env = SubprocVecEnv([self.makeEnv(rank, i) for i in range(self.num_cpu)])
        else:
            if self.policy == "CnnLnLstmPolicy" or self.policy == "CnnLstmPolicy":
                self.env = SubprocVecEnv([self.makeEnv(rank, i) for i in range(self.num_cpu)])
            elif self.policy == "CnnPolicy":
                self.env = CustomEnv()
                #  self.env = DummyVecEnv([lambda : env])

        #  check_env(env)
        return True

    def loadEnv(self):
        if self.env_name == "CustomEnv":
            return self.loadCostumEnv()
        return self.loadGymEnv()

    def getModelCommonName(self):
        model_common_name = self.platform + "_" + self.method
        model_common_name += "_EnvName_" + self.env_name
        model_common_name += "_Policy_" + self.policy
        model_common_name += "_GlobalSeed_" + str(self.global_seed)
        model_common_name += "_Lr_" + str(self.lr)
        model_common_name += "_EntCoef_" + str(self.ent_coef)
        return model_common_name

    def getModelName(self, step):
        model_common_name = self.getModelCommonName()
        model_name = model_common_name + "_Step_" + str(step)
        return model_name

    def loadTrainedModelParam(self):
        self.start_step_num = 0

        file_list = os.listdir(self.model_save_path)

        find_trained_model = False
        model_common_name = self.getModelCommonName()
        for file_name in file_list:
            if model_common_name in file_name:
                step = int(file_name.split(".")[0].split("_Step_")[1])

                if step > self.start_step_num:
                    self.start_step_num = step
                    find_trained_model = True
        return find_trained_model

    def loadModel(self):
        self.model = None

        if self.env is None:
            print("SB3_PPO_Trainer::loadModel: env not loaded!")
            return False

        if self.loadTrainedModelParam():
            trained_model_name = self.getModelName(self.start_step_num)
            trained_model_path = self.model_save_path + trained_model_name
            self.model = Method.load(
                trained_model_path,
                self.env,
                tensorboard_log=self.log_dir)
            return True

        if self.env_name == "CustomEnv":
            self.model = Method(
                self.policy,
                self.env,
                verbose=self.verbose,
                learning_rate=self.lr,
                ent_coef=self.ent_coef,
                tensorboard_log=self.log_dir)
            return True

        self.model = Method(
            "MlpPolicy",
            self.env,
            verbose=self.verbose,
            tensorboard_log=self.log_dir)
        return True

    def initEnv(self):
        print("start updatePath...")
        if not self.updatePath():
            print("update model_save_path and log_dir failed!")
            return False
        print("SUCCESS!")

        print("start loadEnv...")
        if not self.loadEnv():
            print("load gym env", self.env_name, "failed!")
            return False
        print("SUCCESS!")

        print("start loadModel...")
        if not self.loadModel():
            print("load model failed!")
            return False
        print("SUCCESS!")
        return True

    def train(self):
        current_episode = 0

        while current_episode != self.train_episode:
            self.model.learn(
                total_timesteps=self.timesteps_per_episode,
                tb_log_name=self.log_dir + "Train/",
                reset_num_timesteps=False)

            try:
                os.remove(self.getModelName(
                    self.start_step_num + current_episode * self.timesteps_per_episode) + ".zip")
            except:
                pass

            current_episode += 1
            
            self.model.save(
                self.getModelName(self.start_step_num + current_episode * self.timesteps_per_episode))

        del self.model
        return True

    def test(self):
        while True:
            obs = self.env.reset()
            if self.policy == "CnnLnLstmPolicy" or self.policy == "CnnLstmPolicy":
                done = [False, False]
                while not all(done):
                    action, _states = self.model.predict(obs)
                    obs, rewards, dones, info = self.env.step(action)
                    self.env.render('human')
                    done = dones
            else:
                done = False
                while not done:
                    action, states = self.model.predict(obs)
                    obs, rewards, dones, info = self.env.step(action)
                    print("a=", action, end="")
                    print(", r=", rewards, end="")
                    print(", tr=", env.episode_reward)
                    if dones:
                        print("=================")
                    self.env.render()
                    done = dones
        return True

    def start(self):
        if self.train_mode:
            return self.train()
        return self.test()

if __name__ == "__main__":
    rl—trainer = RL_Trainer()
    rl_trainer.initEnv()
    rl_trainer.start()

