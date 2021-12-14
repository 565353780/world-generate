#!/usr/bin/env python
# -*- coding: utf-8 -*-

import numpy as np
import cv2

class WorldGenerateObservation(object):

    def __init__(self):
        # channels : scene, wall, room, free, connect
        self.scene_channel_idx = 0
        self.wall_channel_idx = 1
        self.room_channel_idx = 2
        self.free_channel_idx = 3
        self.connect_channel_idx = 4
        self.image_channels = 5

        self.observation = None

        self.image_width = None
        self.image_height = None
        self.free_area_width = None

        self.outerwall_boundary_data_vec = None
        self.innerwall_boundary_data_vec = None
        self.wallroom_boundary_data_vec = None
        return

    def initObservation(self, width, height, free):
        self.image_width = width
        self.image_height = height
        self.free_area_width = free
        return True

    def transData(self, source_data_vec):
        trans_data_vec = np.array(source_data_vec, dtype=np.uint)
        return trans_data_vec

    def getWorldBoundaryData(self, world_environment):
        self.outerwall_boundary_data_vec = world_environment.getOuterWallBoundaryDataVec()
        self.innerwall_boundary_data_vec = world_environment.getInnerWallBoundaryDataVec()
        self.wallroom_boundary_data_vec = world_environment.getWallRoomBoundaryDataVec()
        return True

    def drawPolyLinesInObservation(self, channel_idx, poly_data, color):
        for polygon in poly_data:
            trans_data = self.transData([polygon])
            cv2.polylines(
                self.observation[channel_idx],
                trans_data,
                True, color)
        return True

    def fillPolyInObservation(self, channel_idx, poly_data, color):
        for polygon in poly_data:
            trans_data = self.transData([polygon])
            cv2.fillPoly(
                self.observation[channel_idx],
                trans_data,
                color)
        return True

    def generateSceneObservation(self):
        self.drawPolyLinesInObservation(self.scene_channel_idx, self.outerwall_boundary_data_vec, 255)
        self.drawPolyLinesInObservation(self.scene_channel_idx, self.innerwall_boundary_data_vec, 255)

        self.fillPolyInObservation(self.scene_channel_idx, self.wallroom_boundary_data_vec, 255)
        return True

    def generateWallObservation(self):
        self.drawPolyLinesInObservation(self.wall_channel_idx, self.outerwall_boundary_data_vec, 255)
        self.drawPolyLinesInObservation(self.wall_channel_idx, self.innerwall_boundary_data_vec, 255)
        return True

    def generateRoomObservation(self):
        self.fillPolyInObservation(self.room_channel_idx, self.wallroom_boundary_data_vec, 255)
        return True

    def generateFreeObservation(self):
        self.fillPolyInObservation(self.free_channel_idx, self.outerwall_boundary_data_vec, 255)
        self.fillPolyInObservation(self.free_channel_idx, self.innerwall_boundary_data_vec, 0)
        self.fillPolyInObservation(self.free_channel_idx, self.wallroom_boundary_data_vec, 0)
        return True

    def generateConnectObservation(self):
        self.fillPolyInObservation(self.connect_channel_idx, self.outerwall_boundary_data_vec, 255)
        self.fillPolyInObservation(self.connect_channel_idx, self.innerwall_boundary_data_vec, 0)

        self.drawPolyLinesInObservation(self.connect_channel_idx, self.wallroom_boundary_data_vec, 0)
        return True

    def updateObservation(self, world_environment):
        self.observation = np.zeros((self.image_channels, self.image_width, self.image_height), dtype=np.uint8)
        self.getWorldBoundaryData(world_environment)
        self.generateSceneObservation()
        self.generateWallObservation()
        self.generateRoomObservation()
        self.generateFreeObservation()
        self.generateConnectObservation()
        return True

    def getObservation(self, world_environment):
        self.updateObservation(world_environment)
        return self.observation

    def getObservationHStack(self):
        return np.hstack((
            self.observation[self.scene_channel_idx],
            self.observation[self.wall_channel_idx],
            self.observation[self.room_channel_idx],
            self.observation[self.free_channel_idx],
            self.observation[self.connect_channel_idx]))

