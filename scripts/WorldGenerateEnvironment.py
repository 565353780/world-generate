#!/usr/bin/env python
# -*- coding: utf-8 -*-

import gym
import numpy as np
import random

from WorldEnvironment import WorldEnvironment

#  world_environment.generateFreeRoomContainer(4, 4, 0.5, 2)

class WorldGenerateEnvironment(gym.Env):
    metadata = {
        'render.modes': ['human'],
        'video.frames_per_second': 2
    }
    
    def __init__(self):
        super(WorldGenerateEnvironment, self).__init__()
        self.world_environment = WorldEnvironment()
        self.wall_edge_num_max = None
        self.outerwall_edge_num_vec = []
        self.innerwall_edge_num_vec = []
        self.outerwall_num = None
        self.innerwall_num = None
        self.container_room_num_max = None

        self.initWorld()

        self.action_space = gym.spaces.Box(
            np.array([
                0.0,
                0.0,
                0.0,
                0.0,
                0.0,
                0.0
            ], dtype=np.float32),
            np.array([
                self.outerwall_num + self.innerwall_num, # wall_idx
                self.wall_edge_num_max,                  # wall_edge_idx
                np.inf,                                  # position
                np.inf,                                  # width
                np.inf,                                  # height
                np.inf                                   # room_num
            ], dtype=np.float32)
        )
        self.observation_space = gym.spaces.Box(low=0, high=255, shape=(3, 1024, 1024), dtype=np.uint8)
        return

    def initWorld(self):
        self.world_environment.createNewWorld(0, 0)

        self.world_environment.createOuterWall()
        self.world_environment.createInnerWall()

        self.world_environment.addPointForOuterWall(0, 0, 0)
        self.world_environment.addPointForOuterWall(0, 30, 0)
        self.world_environment.addPointForOuterWall(0, 30, 30)
        self.world_environment.addPointForOuterWall(0, 0, 30)

        self.world_environment.addPointForInnerWall(0, 10, 10)
        self.world_environment.addPointForInnerWall(0, 20, 10)
        self.world_environment.addPointForInnerWall(0, 20, 20)
        self.world_environment.addPointForInnerWall(0, 10, 20)

        self.world_environment.generateWall()

        self.wall_edge_num_max = 4
        self.outerwall_edge_num_vec = [4]
        self.innerwall_edge_num_vec = [4]
        self.outerwall_num = 1
        self.innerwall_num = 1
        self.container_room_num_max = 4

        self.observation = np.zeros((4, 256, 256))

        self.run_time = 0
        return

    def step(self, action):
        if not self.action_space.contains(action):
            print("WorldGenerateEnvironment::step :\nthis action is not valid!")
            return None, None, None, {}

        reward = 1
        done = False
        self.run_time += 1
        if self.run_time > 10:
            done = True

        wall_idx = int(action[0])
        wall_edge_idx = int(action[1])
        room_num = int(action[5])
        if room_num == 0:
            room_num = 1

        if wall_idx >= self.outerwall_num + self.innerwall_num:
            return self.observation, -100, done, {}

        if wall_idx < self.outerwall_num:
            if wall_edge_idx >= self.outerwall_edge_num_vec[wall_idx]:
                return self.observation, -100, done, {}
        elif wall_edge_idx >= self.innerwall_edge_num_vec[wall_idx - self.outerwall_num]:
            return self.observation, -100, done, {}

        if wall_idx < self.outerwall_num:
            self.world_environment.placeOuterWallRoomContainer(
                wall_idx,
                wall_edge_idx,
                action[2],
                action[3],
                action[4],
                room_num)
        else:
            self.world_environment.placeInnerWallRoomContainer(
                wall_idx - self.outerwall_num,
                wall_edge_idx,
                action[2],
                action[3],
                action[4],
                room_num)

        return self.observation, reward, done, {}

        #  reward = self.world_environment.getReward()
        reward = 1
        done = False
        self.run_time += 1
        if self.run_time > 10:
            done = True

        return self.observation, reward, done, {}

    def reset(self):
        self.world_environment.resetButRemainWall()
        return self.observation

    def render(self, mode="human"):
        return None

    def close(self):
        self.world_environment.reset()
        return None

    def seed(self, seed=None):
        if seed is not None:
            random.seed(seed)

