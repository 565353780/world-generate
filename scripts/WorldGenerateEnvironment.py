#!/usr/bin/env python
# -*- coding: utf-8 -*-

import cv2
import gym
import numpy as np
import random
from math import cos, sin, pi

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
        self.observation_free = 5

        self.step_weight = 0.1
        self.place_failed_weight = 100
        self.space_utilization_weight = 2000
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
            shape=(6, self.observation_width, self.observation_height),
            dtype=np.uint8)

        self.world_generate_observation.initObservation(
            self.observation_width,
            self.observation_height,
            self.observation_free)
        self.observation = self.world_generate_observation.getObservation(self.world_environment)

        self.world_generate_reward.initReward(
            self.step_weight,
            self.place_failed_weight,
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

        a = 18
        b = 10
        point_num = 100
        for i in range(point_num):
            self.world_environment.addPointForOuterWall(
                0, a * cos(2.0 * pi * i / point_num), b * sin(2.0 * pi * i / point_num))

        a = 11
        b = 4
        point_num = 50
        for i in range(point_num):
            self.world_environment.addPointForInnerWall(
                0, a * cos(2.0 * pi * i / point_num), b * sin(2.0 * pi * i / point_num))

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
        if self.run_time > 10:
            self.run_time = 0
            self.done = True

        position_x = int(action[0] * (self.observation_width - 1))
        position_y = int(action[1] * (self.observation_height - 1))

        self.world_environment.placeWallRoomByPosition(position_x, position_y, 2.0, 2.0)

        self.observation = self.world_generate_observation.getObservation(self.world_environment)
        self.reward = self.world_generate_reward.getReward(self.observation, action)

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
        return None

    def random_test(self):
        done = False
        while not done:
            observation, reward, done, info = self.step(
                self.action_space.sample())
            self.render()
            print("reward =", self.episode_reward)
        self.reset()
        self.render()
        return True

    def user_test(self):
        def cv_onMouse(event, x, y, flags, param):
            if event == cv2.EVENT_LBUTTONDOWN:
                action = [1.0 * x / self.observation_width, 1.0 * y / self.observation_height]
                print("press at ", action)
                observation, reward, done, info = self.step(action)
                print("step reward =", reward)
                print("total reward =", self.episode_reward)
                if done:
                    print("=====================================")
            return

        window_name = "user_test_observation"
        cv2.namedWindow(window_name, 1)
        obs_hstack = self.world_generate_observation.getObservationHStack()
        cv2.setMouseCallback(window_name, cv_onMouse, obs_hstack)
        while True:
            obs_hstack = self.world_generate_observation.getObservationHStack()
            cv2.imshow(window_name, obs_hstack)
            key = cv2.waitKey(30)
            if key == 27:
                break
        cv2.destoryAllWindows()
        return None

if __name__ == "__main__":
    world_generate_environment = WorldGenerateEnvironment()
    world_generate_environment.user_test()
    exit()
    while True:
        world_generate_environment.random_test()

