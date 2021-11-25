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

        self.outerwall_boundary_xy_data_vec = None
        self.innerwall_boundary_xy_data_vec = None
        self.roomcontainer_boundary_xy_data_vec = None
        self.wallroom_boundary_xy_data_vec = None
        self.freeroom_boundary_xy_data_vec = None
        self.door_boundary_xy_data_vec = None
        self.window_boundary_xy_data_vec = None
        self.team_boundary_xy_data_vec = None
        self.person_boundary_xy_data_vec = None
        self.furniture_boundary_xy_data_vec = None

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

    def getWorldXYData(self, world_environment):
        self.outerwall_boundary_xy_data_vec = world_environment.getOuterWallBoundaryXYDataVec()
        self.innerwall_boundary_xy_data_vec = world_environment.getInnerWallBoundaryXYDataVec()
        self.roomcontainer_boundary_xy_data_vec = world_environment.getRoomContainerBoundaryXYDataVec()
        self.wallroom_boundary_xy_data_vec = world_environment.getWallRoomBoundaryXYDataVec()
        self.freeroom_boundary_xy_data_vec = world_environment.getFreeRoomBoundaryXYDataVec()
        self.door_boundary_xy_data_vec = world_environment.getDoorBoundaryXYDataVec()
        self.window_boundary_xy_data_vec = world_environment.getWindowBoundaryXYDataVec()
        self.team_boundary_xy_data_vec = world_environment.getTeamBoundaryXYDataVec()
        self.person_boundary_xy_data_vec = world_environment.getPersonBoundaryXYDataVec()
        self.furniture_boundary_xy_data_vec = world_environment.getFurnitureBoundaryXYDataVec()
        return True

    def getImageTransform(self):
        outerwall_num = len(self.outerwall_boundary_xy_data_vec)
        if outerwall_num == 0:
            print("WorldGenerateObservation::getImageScale :\nouterwall not exist!")
            return False
        if len(self.outerwall_boundary_xy_data_vec[0]) == 0:
            print("WorldGenerateObservation::getImageScale :\nouterwall data not exist!")
            return False

        x_min = self.outerwall_boundary_xy_data_vec[0][0]
        y_min = self.outerwall_boundary_xy_data_vec[0][1]
        x_max = self.outerwall_boundary_xy_data_vec[0][0]
        y_max = self.outerwall_boundary_xy_data_vec[0][1]
        for i in range(outerwall_num):
            outerwall_boundary_point_num = int(len(self.outerwall_boundary_xy_data_vec[i]) / 2)
            for j in range(outerwall_boundary_point_num):
                outerwall_boundary_point_idx = 2 * j
                x_min = min(x_min, self.outerwall_boundary_xy_data_vec[i][outerwall_boundary_point_idx])
                y_min = min(y_min, self.outerwall_boundary_xy_data_vec[i][outerwall_boundary_point_idx + 1])
                x_max = max(x_max, self.outerwall_boundary_xy_data_vec[i][outerwall_boundary_point_idx])
                y_max = max(y_max, self.outerwall_boundary_xy_data_vec[i][outerwall_boundary_point_idx + 1])

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

    def getPointInWorld(self, x, y):
        x_in_world = x / self.scale - self.offset[0]
        y_in_world = y / self.scale - self.offset[1]
        return x_in_world, y_in_world

    def getObservation(self, world_environment):
        self.getWorldXYData(world_environment)
        self.getImageTransform()

        return self.observation

