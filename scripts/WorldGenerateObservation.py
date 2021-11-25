#!/usr/bin/env python
# -*- coding: utf-8 -*-

import numpy as np
import cv2

class WorldGenerateObservation(object):

    def __init__(self):
        self.observation = None

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
        return

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
        print(self.outerwall_boundary_xy_data_vec)
        exit()
        return

