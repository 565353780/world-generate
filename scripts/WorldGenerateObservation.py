#!/usr/bin/env python
# -*- coding: utf-8 -*-

import numpy as np
import cv2

class WorldGenerateObservation(object):

    def __init__(self):
        self.observation = None

        self.image_width = None
        self.image_height = None
        self.offset = None
        self.scale = None

        self.outerwall_boundary_data_vec = None
        self.innerwall_boundary_data_vec = None
        self.roomcontainer_boundary_data_vec = None
        self.wallroom_boundary_data_vec = None
        self.freeroom_boundary_data_vec = None
        self.door_boundary_data_vec = None
        self.window_boundary_data_vec = None
        self.team_boundary_data_vec = None
        self.person_boundary_data_vec = None
        self.furniture_boundary_data_vec = None

        self.wall_channel_idx = 0
        self.room_channel_idx = 1
        self.obstacle_channel_idx = 2
        return

    def initObservation(self, width, height):
        self.image_width = width
        self.image_height = height

        # channels : wall, room, obstacle
        self.observation = np.zeros((3, self.image_width, self.image_height))
        return True

    def getWorldBoundaryData(self, world_environment):
        self.outerwall_boundary_data_vec = world_environment.getOuterWallBoundaryDataVec()
        self.innerwall_boundary_data_vec = world_environment.getInnerWallBoundaryDataVec()
        self.roomcontainer_boundary_data_vec = world_environment.getRoomContainerBoundaryDataVec()
        self.wallroom_boundary_data_vec = world_environment.getWallRoomBoundaryDataVec()
        self.freeroom_boundary_data_vec = world_environment.getFreeRoomBoundaryDataVec()
        self.door_boundary_data_vec = world_environment.getDoorBoundaryDataVec()
        self.window_boundary_data_vec = world_environment.getWindowBoundaryDataVec()
        self.team_boundary_data_vec = world_environment.getTeamBoundaryDataVec()
        self.person_boundary_data_vec = world_environment.getPersonBoundaryDataVec()
        self.furniture_boundary_data_vec = world_environment.getFurnitureBoundaryDataVec()
        return True

    def getImageTransform(self):
        outerwall_num = len(self.outerwall_boundary_data_vec)
        if outerwall_num == 0:
            print("WorldGenerateObservation::getImageScale :\nouterwall not exist!")
            return False
        if len(self.outerwall_boundary_data_vec[0]) == 0:
            print("WorldGenerateObservation::getImageScale :\nouterwall data not exist!")
            return False

        x_min = self.outerwall_boundary_data_vec[0][0][0]
        y_min = self.outerwall_boundary_data_vec[0][0][1]
        x_max = self.outerwall_boundary_data_vec[0][0][0]
        y_max = self.outerwall_boundary_data_vec[0][0][1]
        for outerwall_boundary_data in self.outerwall_boundary_data_vec:
            for outerwall_boundary_point in outerwall_boundary_data:
                x_min = min(x_min, outerwall_boundary_point[0])
                y_min = min(y_min, outerwall_boundary_point[1])
                x_max = max(x_max, outerwall_boundary_point[0])
                y_max = max(y_max, outerwall_boundary_point[1])

        x_diff = x_max - x_min
        if x_diff == 0:
            print("WorldGenerateObservation::getImageScale :\nouterwall x_diff not valid!")
            return False
        y_diff = y_max - y_min
        if y_diff == 0:
            print("WorldGenerateObservation::getImageScale :\nouterwall y_diff not valid!")
            return False

        self.offset = [-x_min, -y_min]
        self.scale = min(self.image_width / x_diff, self.image_height / y_diff)
        return True

    def getPointInImage(self, x, y):
        x_in_image = (x + self.offset[0]) * self.scale
        y_in_image = (y + self.offset[1]) * self.scale
        return x_in_image, y_in_image
    def getPointInImage(self, point):
        x = point[0]
        y = point[1]
        x_in_image, y_in_image = self.getPointInImage(x, y)
        return [x_in_image, y_in_image]

    def getPointInWorld(self, x, y):
        x_in_world = x / self.scale - self.offset[0]
        y_in_world = y / self.scale - self.offset[1]
        return x_in_world, y_in_world
    def getPointInWorld(self, point):
        x = point[0]
        y = point[1]
        x_in_world, y_in_world = self.getPointInWorld(x, y)
        return [x_in_world, y_in_world]

    def fillWallInObservation(self):
        cv2.polylines(
            self.observation[self.wall_channel_idx],
            np.array(self.outerwall_boundary_data_vec, dtype=np.int32),
            True,
            255)

        cv2.imshow("wall channel", self.observation[self.wall_channel_idx])
        cv2.waitKey(0)
        return True

    def getObservation(self, world_environment):
        self.getWorldBoundaryData(world_environment)
        self.getImageTransform()
        self.fillWallInObservation()

        return self.observation

