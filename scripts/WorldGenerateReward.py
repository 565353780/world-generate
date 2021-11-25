#!/usr/bin/env python
# -*- coding: utf-8 -*-

import numpy as np
import cv2

class WorldGenerateReward(object):

    def __init__(self):
        self.scene_channel_idx = 0
        self.wall_channel_idx = 1
        self.room_channel_idx = 2
        self.free_channel_idx = 3
        self.connect_channel_idx = 4

        self.reward = None

        self.space_utilization_weight = None
        self.movable_weight = None
        self.escapable_weight = None

        self.previous_observation = None

        self.space_utilization_score = None
        self.movable_score = None
        self.escapable_score = None

        self.previous_space_utilization_score = None
        self.previous_movable_score = None
        self.previous_escapable_score = None

    def initReward(self, space_utilization_weight, movable_weight, escapable_weight):
        self.space_utilization_weight = space_utilization_weight
        self.movable_weight = movable_weight
        self.escapable_weight = escapable_weight
        return True

    def getSpaceUtilizationScore(self, observation):
        self.space_utilization_score = float(np.sum(observation[self.room_channel_idx] > 0))
        return True

    def getMovableScore(self, observation):
        connected_areas_num, pixel_labels = cv2.connectedComponents(observation[self.free_channel_idx])
        self.movable_score = connected_areas_num
        return True

    def getEscapableScore(self, observation):
        connected_areas_num, pixel_labels = cv2.connectedComponents(observation[self.connect_channel_idx])
        self.escapable_score = connected_areas_num
        return True

    def updateReward(self, observation):
        self.reward = 0
        self.getSpaceUtilizationScore(observation)
        self.getMovableScore(observation)
        self.getEscapableScore(observation)

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

    def getReward(self, observation):
        self.updateReward(observation)
        return self.reward

