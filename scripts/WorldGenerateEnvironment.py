#!/usr/bin/env python
# -*- coding: utf-8 -*-

import cv2
import gym
import numpy as np
import random

#  from WorldEnvironment import WorldEnvironment
from UnitWorldEnvironment import UnitWorldEnvironment as WorldEnvironment

from WorldGenerateObservation import WorldGenerateObservation
from WorldGenerateReward import WorldGenerateReward

class WorldGenerateEnvironment(gym.Env):
    metadata = {
        'render.modes': ['human']
    }
    
    def __init__(self):
        super(WorldGenerateEnvironment, self).__init__()
        self.world_environment = WorldEnvironment()
        self.world_generate_observation = WorldGenerateObservation()
        self.world_generate_reward = WorldGenerateReward()

        self.observation_width = 256
        self.observation_height = 256
        self.observation_free = 20

        self.step_weight = 1
        self.space_utilization_weight = 0.1
        self.movable_weight = 1
        self.escapable_weight = 1

        self.width_prefix = 4
        self.height_prefix = 4
        self.room_num_prefix = 1

        self.wall_edge_num_max = None
        self.outerwall_edge_num_vec = []
        self.innerwall_edge_num_vec = []
        self.outerwall_num = None
        self.innerwall_num = None
        self.container_room_num_max = None
        self.wall_length_max = None

        self.initWorld()

        self.action_space = gym.spaces.Box(
            np.array([0.0, 0.0], dtype=np.float32),
            np.array([1.0, 1.0], dtype=np.float32)
        )
        self.observation_space = gym.spaces.Box(
            low=0,
            high=255,
            shape=(5, self.observation_width, self.observation_height),
            dtype=np.uint8)

        self.world_generate_observation.initObservation(
            self.observation_width,
            self.observation_height,
            self.observation_free)
        self.observation = self.world_generate_observation.getObservation(self.world_environment)

        self.world_generate_reward.initReward(
            self.step_weight,
            self.space_utilization_weight,
            self.movable_weight,
            self.escapable_weight)
        self.reward = self.world_generate_reward.getReward(self.observation)

        self.done = None
        self.episode_reward = 0
        self.writer = None
        self.env_idx = None
        self.round = 0
        return

    def initWorld(self):
        self.world_environment.setImageSize(
            self.observation_width, self.observation_height, self.observation_free)

        self.world_environment.createNewWorld()

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

        self.run_time = 0
        return

    def setWriter(self, writer, env_idx):
        self.writer = writer
        self.env_idx = env_idx

    def afterStep(self):
        self.episode_reward += self.reward
        if self.done:
            if self.writer is not None:
                self.writer.add_scalar(
                    "Reward/reward_" + str(self.env_idx), self.episode_reward, self.round)
            self.episode_reward = 0
            self.round += 1
        return self.observation, self.reward, self.done, {}

    def step(self, action):
        self.done = False
        self.run_time += 1
        if self.run_time > 34:
            self.run_time = 0
            self.done = True

        position_x = int(action[0] * (self.observation_width - 1))
        position_y = int(action[1] * (self.observation_height - 1))

        self.world_environment.placeWallRoomByPosition(
            position_x, position_y)

        self.observation = self.world_generate_observation.getObservation(self.world_environment)
        self.reward = self.world_generate_reward.getReward(self.observation)

        return self.afterStep()

    def reset(self):
        self.world_environment.resetButRemainWall()
        self.observation = self.world_generate_observation.getObservation(self.world_environment)
        self.reward = self.world_generate_reward.getReward(self.observation)
        return self.observation

    def render(self, mode="human"):
        obs_hstack = self.world_generate_observation.getObservationHStack()
        cv2.imshow("observation", obs_hstack)
        cv2.waitKey(200)
        return None

    def close(self):
        self.world_environment.reset()
        return None

    def seed(self, seed=None):
        if seed is not None:
            random.seed(seed)

if __name__ == "__main__":
    world_generate_environment = WorldGenerateEnvironment()
    print("init finished!")
    done = False
    while not done:
        print("step!")
        _, _, done, _ = world_generate_environment.step(world_generate_environment.action_space.sample())
        world_generate_environment.render()
    print("finish test episode, start render episode")
    world_generate_environment.reset()
    world_generate_environment.render()

    world_generate_environment.step(world_generate_environment.action_space.sample())
    world_generate_environment.render()
    world_generate_environment.step(world_generate_environment.action_space.sample())
    world_generate_environment.render()
    world_generate_environment.step(world_generate_environment.action_space.sample())
    world_generate_environment.render()
    world_generate_environment.step(world_generate_environment.action_space.sample())
    world_generate_environment.render()
    world_generate_environment.reset()
    world_generate_environment.render()
    world_generate_environment.step(world_generate_environment.action_space.sample())
    world_generate_environment.render()
    world_generate_environment.step(world_generate_environment.action_space.sample())
    world_generate_environment.render()
    world_generate_environment.step(world_generate_environment.action_space.sample())
    world_generate_environment.render()
    world_generate_environment.step(world_generate_environment.action_space.sample())
    world_generate_environment.render()
    world_generate_environment.reset()
    print("finish render episode")

