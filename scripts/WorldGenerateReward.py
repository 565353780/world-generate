#!/usr/bin/env python
# -*- coding: utf-8 -*-

import numpy as np
import cv2

class WorldGenerateReward(object):

    def __init__(self):
        self.scene_channel_idx = 0
        self.wall_channel_idx = 1
        self.place_channel_idx = 2
        self.room_channel_idx = 3
        self.free_channel_idx = 4
        self.connect_channel_idx = 5

        self.reward = None

        self.step_weight = None
        self.place_failed_weight = None
        self.space_utilization_weight = None
        self.movable_weight = None
        self.escapable_weight = None

        self.step_score = None
        self.place_failed_score = None
        self.space_utilization_score = None
        self.movable_score = None
        self.escapable_score = None

        self.previous_space_utilization_score = None
        self.previous_movable_score = None
        self.previous_escapable_score = None

    def initReward(self,
                   step_weight,
                   place_failed_weight,
                   space_utilization_weight,
                   movable_weight,
                   escapable_weight):
        self.step_weight = step_weight
        self.place_failed_weight = place_failed_weight
        self.space_utilization_weight = space_utilization_weight
        self.movable_weight = movable_weight
        self.escapable_weight = escapable_weight
        return True

    def getStepScore(self):
        self.step_score = 1
        return True

    def getPlaceFailedScore(self, observation, action):
        self.place_failed_score = 0

        if action is None:
            return True

        action_x = int((observation.shape[1] - 1) * action[0])
        action_y = int((observation.shape[2] - 1) * action[1])
        if observation[self.place_channel_idx][action_y][action_x] > 0:
            return True

        max_search_width = max(observation.shape[1] - 1, observation.shape[2] - 1)
        search_width = 1
        while search_width < max_search_width:
            for x in range(-search_width, search_width + 1):
                search_x = action_x + x
                if search_x < 0 or search_x >= observation.shape[1]:
                    continue
                for y in [-search_width, search_width]:
                    search_y = action_y + y
                    if search_y < 0 or search_y >= observation.shape[2]:
                        continue
                    if observation[self.place_channel_idx][search_y][search_x] > 0:
                        return True
            for y in range(-search_width, search_width + 1):
                search_y = action_y + y
                if search_y < 0 or search_y >= observation.shape[2]:
                    continue
                for x in [-search_width, search_width]:
                    search_x = action_x + x
                    if search_x < 0 or search_x >= observation.shape[1]:
                        continue
                    if observation[self.place_channel_idx][search_y][search_x] > 0:
                        return True
            self.place_failed_score += 1.0 / max_search_width
            search_width += 1
        return True

    def getSpaceUtilizationScore(self, observation):
        self.space_utilization_score = float(np.sum(observation[self.room_channel_idx] > 0))
        self.space_utilization_score /= observation.shape[1] * observation.shape[2]
        return True

    def getMovableScore(self, observation):
        connected_areas_num, pixel_labels = cv2.connectedComponents(observation[self.free_channel_idx])
        self.movable_score = connected_areas_num
        return True

    def getEscapableScore(self, observation):
        connected_areas_num, pixel_labels = cv2.connectedComponents(observation[self.connect_channel_idx])
        self.escapable_score = connected_areas_num
        return True

    def updateReward(self, observation, action):
        self.reward = 0
        self.getStepScore()
        self.getPlaceFailedScore(observation, action)
        self.getSpaceUtilizationScore(observation)
        self.getMovableScore(observation)
        self.getEscapableScore(observation)

        self.reward -= self.step_weight * self.step_score
        self.reward -= self.place_failed_weight * self.place_failed_score

        if self.previous_space_utilization_score is None:
            self.reward += self.space_utilization_weight * self.space_utilization_score
        else:
            self.reward += self.space_utilization_weight * \
                (self.space_utilization_score - self.previous_space_utilization_score)
            self.reward -= self.movable_weight * \
                (self.movable_score - self.previous_movable_score)
            self.reward -= self.escapable_weight * \
                (self.escapable_score - self.previous_escapable_score)

        self.previous_space_utilization_score = self.space_utilization_score
        self.previous_movable_score = self.movable_score
        self.previous_escapable_score = self.escapable_score
        return True

    def getReward(self, observation, action=None):
        self.updateReward(observation, action)
        if self.space_utilization_score == self.previous_space_utilization_score:
            self.reward -= 10 * self.step_weight
        return self.reward

