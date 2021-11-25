#!/usr/bin/env python
# -*- coding: utf-8 -*-

import gym
import numpy as np
import random

from WorldEnvironment import WorldEnvironment
from WorldGenerateObservation import WorldGenerateObservation
from WorldGenerateReward import WorldGenerateReward

#  world_environment.generateFreeRoomContainer(4, 4, 0.5, 2)

class WorldGenerateEnvironment(gym.Env):
    metadata = {
        'render.modes': ['human'],
        'video.frames_per_second': 2
    }
    
    def __init__(self):
        super(WorldGenerateEnvironment, self).__init__()
        self.world_environment = WorldEnvironment()
        self.world_generate_observation = WorldGenerateObservation()
        self.world_generate_reward = WorldGenerateReward()

        self.observation_width = 256
        self.observation_height = 256
        self.observation_free = 20

        self.wall_edge_num_max = None
        self.outerwall_edge_num_vec = []
        self.innerwall_edge_num_vec = []
        self.outerwall_num = None
        self.innerwall_num = None
        self.container_room_num_max = None
        self.wall_length_max = None

        self.width_prefix = 4
        self.height_prefix = 4
        self.room_num_prefix = 1

        self.initWorld()

        self.action_space = gym.spaces.Box(
            np.array([
                0.0,
                0.0,
                0.0
            ], dtype=np.float32),
            np.array([
                self.outerwall_num + self.innerwall_num, # wall_idx
                self.wall_edge_num_max,                  # wall_edge_idx
                self.wall_length_max                     # position
            ], dtype=np.float32)
        )
        self.observation_space = gym.spaces.Box(low=0, high=255, shape=(4, self.observation_width, self.observation_height), dtype=np.uint8)

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
        self.wall_length_max = 30

        self.world_generate_observation.initObservation(
            self.observation_width,
            self.observation_height,
            self.observation_free)

        self.world_generate_observation.updateObservation(self.world_environment)

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
        room_position = action[2]
        #  room_num = int(action[5])
        room_num = int(self.room_num_prefix)
        if room_num == 0:
            room_num = 1

        if wall_idx >= self.outerwall_num + self.innerwall_num:
            return self.world_generate_observation.observation, -100, done, {}

        if wall_idx < self.outerwall_num:
            if wall_edge_idx >= self.outerwall_edge_num_vec[wall_idx]:
                return self.world_generate_observation.observation, -100, done, {}
        elif wall_edge_idx >= self.innerwall_edge_num_vec[wall_idx - self.outerwall_num]:
            return self.world_generate_observation.observation, -100, done, {}

        if wall_idx < self.outerwall_num:
            self.world_environment.placeOuterWallRoomContainer(
                wall_idx,
                wall_edge_idx,
                room_position,
                self.width_prefix,
                self.height_prefix,
                self.room_num_prefix)
        else:
            self.world_environment.placeInnerWallRoomContainer(
                wall_idx - self.outerwall_num,
                wall_edge_idx,
                room_position,
                self.width_prefix,
                self.height_prefix,
                self.room_num_prefix)

        self.world_generate_observation.updateObservation(self.world_environment)

        return self.world_generate_observation.observation, reward, done, {}

        #  reward = self.world_environment.getReward()
        reward = 1
        done = False
        self.run_time += 1
        if self.run_time > 10:
            done = True

        return self.world_generate_observation.observation, reward, done, {}

    def reset(self):
        self.world_environment.resetButRemainWall()
        self.world_generate_observation.updateObservation(self.world_environment)
        return self.world_generate_observation.observation

    def render(self, mode="human"):
        return None

    def close(self):
        self.world_environment.reset()
        return None

    def seed(self, seed=None):
        if seed is not None:
            random.seed(seed)

if __name__ == "__main__":
    world_generate_environment = WorldGenerateEnvironment()
    world_generate_environment.step([0, 0, 0])
    world_generate_environment.reset()

