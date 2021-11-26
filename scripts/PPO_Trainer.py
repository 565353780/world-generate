#!/usr/bin/env python
# -*- coding: utf-8 -*-

import os
import gym

from stable_baselines3 import PPO
from stable_baselines3.common.env_checker import check_env
from stable_baselines3.common.env_util import make_vec_env
from stable_baselines3.common.vec_env import DummyVecEnv, SubprocVecEnv, VecNormalize, VecFrameStack

from WorldGenerateEnvironment import WorldGenerateEnvironment

if __name__ == "__main__":
    game_name = "MyEnv"
    train_mode = True
    policy = "CnnPolicy"
    log_dir = "./tmp/"
    start_episode = 0
    total_time_step =50000
    num_cpu = 6
    global_seeds = 0

    def set_global_seeds(seed=0):
        global_seeds = seed

    def make_env(rank, seed=0):
        def _init():
            env = WorldGenerateEnvironment()
            return env
        set_global_seeds(seed)
        return _init
    
    def make_framestack_env(rank, seed=0):
        def _init():
            env = WorldGenerateEnvironment()
            env = DummyVecEnv([lambda : env])
            env = VecFrameStack(env, n_stack=4)
            return env
        set_global_seeds(seed)
        return _init

    env = None
    if game_name == "MyEnv":
        if train_mode:
            if policy == "CnnLnLstmPolicy" or policy == "CnnLstmPolicy":
                env = SubprocVecEnv([make_env(10, i) for i in range(num_cpu)])
            elif policy == "CnnPolicy":
                env = SubprocVecEnv([make_env(10, i) for i in range(num_cpu)])
        else:
            if policy == "CnnLnLstmPolicy" or policy == "CnnLstmPolicy":
                env = SubprocVecEnv([make_env(10, i) for i in range(num_cpu)])
            elif policy == "CnnPolicy":
                env = WorldGenerateEnvironment()
                env = DummyVecEnv([lambda : env])
    else:
        if train_mode:
            env = make_vec_env(game_name, n_envs=4)
        else:
            env = make_vec_env(game_name, n_envs=1)

    #  check_env(env)

    model = None
    start_step_num = 0

    if start_episode > 0:
        model = PPO.load(
            "PPO_" + game_name + "_" + str(start_episode),
            env,
            tensorboard_log="./PPO_WE_tb/")
    else:
        file_list = os.listdir(os.getcwd())

        for file_name in file_list:
            if "PPO_" + game_name + "_" in file_name:
                current_step_num = int(file_name.split(".")[0].split("_")[2])

                if current_step_num > start_step_num:
                    start_step_num = current_step_num
        
        if start_step_num > 0:
            model = PPO.load(
                "PPO_" + game_name + "_" + str(start_step_num),
                env,
                tensorboard_log="./PPO_WE_tb/")
        else:
            if game_name == "MyEnv":
                model = PPO(
                    policy,
                    env,
                    verbose=1,
                    tensorboard_log="./PPO_WE_tb/")
            else:
                model = PPO(
                    "MlpPolicy",
                    env,
                    verbose=1,
                    tensorboard_log="./PPO_WE_tb/")

    if train_mode:
        round = 0

        model.learning_rate = 1e-4

        while True:
            model.learn(
                total_timesteps=total_time_step,
                tb_log_name="PPO_WE_run",
                reset_num_timesteps=False)

            try:
                os.remove("PPO_" + game_name + "_" + str(start_step_num + round * total_time_step) + ".zip")
            except:
                pass

            round += 1
            
            model.save("PPO_" + game_name + "_" + str(start_step_num + round * total_time_step))

        del model
    else:
        while True:
            obs = env.reset()
            if policy == "CnnLnLstmPolicy" or policy == "CnnLstmPolicy":
                done = [False, False]
                while not all(done):
                    action, _states = model.predict(obs)
                    obs, rewards, dones, info = env.step(action)
                    env.render('human')
                    done = dones
            else:
                done = False
                while not done:
                    action, _states = model.predict(obs)
                    obs, rewards, dones, info = env.step(action)
                    env.render()
                    done = dones

