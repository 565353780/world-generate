#!/usr/bin/env python
# -*- coding: utf-8 -*-

import numpy as np
import cv2

class WorldGenerateObservation(object):

    def __init__(self):
        self.observation = None

        self.image_width = None
        self.image_height = None
        self.free_area_width = None
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

        self.outerwall_boundary_data_vec_in_image = None
        self.innerwall_boundary_data_vec_in_image = None
        self.roomcontainer_boundary_data_vec_in_image = None
        self.wallroom_boundary_data_vec_in_image = None
        self.freeroom_boundary_data_vec_in_image = None
        self.door_boundary_data_vec_in_image = None
        self.window_boundary_data_vec_in_image = None
        self.team_boundary_data_vec_in_image = None
        self.person_boundary_data_vec_in_image = None
        self.furniture_boundary_data_vec_in_image = None

        self.scene_channel_idx = 0
        self.wall_channel_idx = 1
        self.room_channel_idx = 2
        self.obstacle_channel_idx = 3
        return

    def initObservation(self, width, height, free):
        self.image_width = width
        self.image_height = height
        self.free_area_width = free

        # channels : scene, wall, room, obstacle
        self.observation = np.zeros((4, self.image_width, self.image_height))
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
        self.scale = min(
            (self.image_width - 2 * self.free_area_width) / x_diff,
            (self.image_height - 2 * self.free_area_width) / y_diff)
        return True

    def getXYInImage(self, x, y):
        x_in_image = (x + self.offset[0]) * self.scale + self.free_area_width
        y_in_image = (y + self.offset[1]) * self.scale + self.free_area_width
        return x_in_image, y_in_image
    def getPointInImage(self, point):
        x = point[0]
        y = point[1]
        x_in_image, y_in_image = self.getXYInImage(x, y)
        return [x_in_image, y_in_image]

    def getXYInWorld(self, x, y):
        x_in_world = (x - self.free_area_width) / self.scale - self.offset[0]
        y_in_world = (y - self.free_area_width) / self.scale - self.offset[1]
        return x_in_world, y_in_world
    def getPointInWorld(self, point):
        x = point[0]
        y = point[1]
        x_in_world, y_in_world = self.getXYInWorld(x, y)
        return [x_in_world, y_in_world]

    def getWorldBoundaryDataVecInImage(self, world_boundary_data_vec):
        world_boundary_data_vec_in_image = []
        for world_boundary_data in world_boundary_data_vec:
            world_boundary_data_in_image = []
            for world_boundary_point in world_boundary_data:
                world_boundary_point_in_image = self.getPointInImage(world_boundary_point)
                world_boundary_data_in_image.append(world_boundary_point_in_image)
            world_boundary_data_vec_in_image.append(world_boundary_data_in_image)
        return np.array(world_boundary_data_vec_in_image, dtype=np.int32)

    def getWorldBoundaryDataInImage(self):
        self.outerwall_boundary_data_vec_in_image = self.getWorldBoundaryDataVecInImage(self.outerwall_boundary_data_vec)
        self.innerwall_boundary_data_vec_in_image = self.getWorldBoundaryDataVecInImage(self.innerwall_boundary_data_vec)
        self.roomcontainer_boundary_data_vec_in_image = self.getWorldBoundaryDataVecInImage(self.roomcontainer_boundary_data_vec)
        self.wallroom_boundary_data_vec_in_image = self.getWorldBoundaryDataVecInImage(self.wallroom_boundary_data_vec)
        self.freeroom_boundary_data_vec_in_image = self.getWorldBoundaryDataVecInImage(self.freeroom_boundary_data_vec)
        self.door_boundary_data_vec_in_image = self.getWorldBoundaryDataVecInImage(self.door_boundary_data_vec)
        self.window_boundary_data_vec_in_image = self.getWorldBoundaryDataVecInImage(self.window_boundary_data_vec)
        self.team_boundary_data_vec_in_image = self.getWorldBoundaryDataVecInImage(self.team_boundary_data_vec)
        self.person_boundary_data_vec_in_image = self.getWorldBoundaryDataVecInImage(self.person_boundary_data_vec)
        self.furniture_boundary_data_vec_in_image = self.getWorldBoundaryDataVecInImage(self.furniture_boundary_data_vec)
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

        self.getImageTransform()
        self.getWorldBoundaryDataInImage()
        return True

    def drawPolyLinesInObservation(self, channel_idx, poly_data, color):
        cv2.polylines(
            self.observation[channel_idx],
            poly_data,
            True, color)
        return True

    def fillPolyInObservation(self, channel_idx, poly_data, color):
        cv2.fillPoly(
            self.observation[channel_idx],
            poly_data,
            color)
        return True

    def generateSceneObservation(self):
        self.drawPolyLinesInObservation(self.scene_channel_idx, self.outerwall_boundary_data_vec_in_image, 255)
        self.drawPolyLinesInObservation(self.scene_channel_idx, self.innerwall_boundary_data_vec_in_image, 255)

        self.fillPolyInObservation(self.scene_channel_idx, self.roomcontainer_boundary_data_vec_in_image, 255)
        return True


    def generateWallObservation(self):
        self.drawPolyLinesInObservation(self.wall_channel_idx, self.outerwall_boundary_data_vec_in_image, 255)
        self.drawPolyLinesInObservation(self.wall_channel_idx, self.innerwall_boundary_data_vec_in_image, 255)
        return True

    def generateRoomObservation(self):
        self.fillPolyInObservation(self.room_channel_idx, self.roomcontainer_boundary_data_vec_in_image, 255)
        return True

    def generateObstacleObservation(self):
        self.drawPolyLinesInObservation(self.obstacle_channel_idx, self.outerwall_boundary_data_vec_in_image, 255)
        self.drawPolyLinesInObservation(self.obstacle_channel_idx, self.innerwall_boundary_data_vec_in_image, 255)
        self.drawPolyLinesInObservation(self.obstacle_channel_idx, self.wallroom_boundary_data_vec_in_image, 255)
        self.drawPolyLinesInObservation(self.obstacle_channel_idx, self.freeroom_boundary_data_vec_in_image, 255)

        self.fillPolyInObservation(self.obstacle_channel_idx, self.furniture_boundary_data_vec_in_image, 255)
        self.fillPolyInObservation(self.obstacle_channel_idx, self.door_boundary_data_vec_in_image, 0)
        return True

    def updateObservation(self, world_environment):
        self.getWorldBoundaryData(world_environment)
        self.generateSceneObservation()
        self.generateWallObservation()
        self.generateRoomObservation()
        self.generateObstacleObservation()

        cv2.imshow("observation", np.hstack((
                       self.observation[self.scene_channel_idx],
                       self.observation[self.wall_channel_idx],
                       self.observation[self.room_channel_idx],
                       self.observation[self.obstacle_channel_idx])))
        cv2.waitKey(0)
        return True

