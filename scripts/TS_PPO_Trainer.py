#!/usr/bin/env python
# -*- coding: utf-8 -*-

import gym, torch, numpy as np, torch.nn as nn
from torch.utils.tensorboard import SummaryWriter
import tianshou as ts

from WorldGenerateEnvironment import WorldGenerateEnvironment

if __name__ == "__main__":
    task = 'CartPole-v0'
    lr, epoch, batch_size = 1e-3, 10, 64
    train_num, test_num = 10, 100
    #  num_cpu = 6
    gamma, n_step, target_freq = 0.9, 3, 320
    buffer_size = 20000
    eps_train, eps_test = 0.1, 0.05
    step_per_epoch, step_per_collect = 10000, 10
    logger = ts.utils.TensorboardLogger(SummaryWriter('log/dqn'))  # TensorBoard is supported!

    def set_global_seeds(seed=0):
        global_seeds = seed

    def make_env(rank, seed=0):
        def _init():
            env = WorldGenerateEnvironment()
            env.setWriter(SummaryWriter(log_dir + "PPO_WE_reward/"), seed)
            return env
        set_global_seeds(seed)
        return _init
    
    def make_framestack_env(rank, seed=0):
        def _init():
            env = WorldGenerateEnvironment()
            env.setWriter(SummaryWriter(log_dir + "PPO_WE_reward/"), seed)
            env = DummyVecEnv([lambda : env])
            env = VecFrameStack(env, n_stack=4)
            return env
        set_global_seeds(seed)
        return _init

    # you can also try with SubprocVectorEnv

    train_envs = ts.env.DummyVectorEnv([lambda: gym.make(task) for _ in range(train_num)])
    test_envs = ts.env.DummyVectorEnv([lambda: gym.make(task) for _ in range(test_num)])

    #  train_envs = ts.env.DummyVectorEnv([lambda: make_env(i) for i in range(train_num)])
    #  test_envs = ts.env.DummyVectorEnv([lambda: make_env(i + train_num) for i in range(test_num)])

    from tianshou.utils.net.common import Net
    # you can define other net by following the API:
    # https://tianshou.readthedocs.io/en/master/tutorials/dqn.html#build-the-network
    env = gym.make(task)
    state_shape = env.observation_space.shape or env.observation_space.n
    action_shape = env.action_space.shape or env.action_space.n
    net = Net(state_shape=state_shape, action_shape=action_shape, hidden_sizes=[128, 128, 128])
    optim = torch.optim.Adam(net.parameters(), lr=lr)

    policy = ts.policy.DQNPolicy(net, optim, gamma, n_step, target_update_freq=target_freq)
    train_collector = ts.data.Collector(
        policy, train_envs, ts.data.VectorReplayBuffer(buffer_size, train_num), exploration_noise=True)
    test_collector = ts.data.Collector(
        policy, test_envs, exploration_noise=True)  # because DQN uses epsilon-greedy method

    result = ts.trainer.offpolicy_trainer(
    policy, train_collector, test_collector, epoch, step_per_epoch, step_per_collect,
    test_num, batch_size, update_per_step=1 / step_per_collect,
    train_fn=lambda epoch, env_step: policy.set_eps(eps_train),
    test_fn=lambda epoch, env_step: policy.set_eps(eps_test),
    stop_fn=lambda mean_rewards: mean_rewards >= env.spec.reward_threshold,
    logger=logger)
    print(f'Finished training! Use {result["duration"]}')

    torch.save(policy.state_dict(), 'dqn.pth')
    policy.load_state_dict(torch.load('dqn.pth'))

    policy.eval()
    policy.set_eps(eps_test)
    collector = ts.data.Collector(policy, env, exploration_noise=True)
    collector.collect(n_episode=1, render=1 / 35)

