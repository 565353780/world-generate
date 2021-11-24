#!/usr/bin/env python
# -*- coding: utf-8 -*-

from WorldEnvironment import WorldEnvironment
from tqdm import tqdm
from time import time
from random import randint

world_environment = WorldEnvironment()

world_environment.createNewWorld(0, 0)

world_environment.createOuterWall()
world_environment.createInnerWall()

world_environment.addPointForOuterWall(0, 0, 0)
world_environment.addPointForOuterWall(0, 41.173, 0)
world_environment.addPointForOuterWall(0, 41.173, 40.978)
world_environment.addPointForOuterWall(0, 0, 40.978)

world_environment.addPointForInnerWall(0, 10, 10)
world_environment.addPointForInnerWall(0, 30, 10)
world_environment.addPointForInnerWall(0, 30, 30)
world_environment.addPointForInnerWall(0, 10, 30)

world_environment.generateWall()

world_environment.placeOuterWallRoomContainer(0, 0, 0, 6.935, 16.169, 1)

world_environment.generateFreeRoomContainer(4, 4, 0.5, 2)

for i in tqdm(range(100)):
    time_start = time()
    world_environment.resetButRemainWall()
    world_environment.placeOuterWallRoomContainer(0, randint(0, 3), randint(0, 21), 4, 4, 1)
    world_environment.placeOuterWallRoomContainer(0, randint(0, 3), randint(0, 11), 12, 4, 3)
    world_environment.placeInnerWallRoomContainer(0, randint(0, 3), randint(0, 21), 4, 4, 1)
    world_environment.placeInnerWallRoomContainer(0, randint(0, 3), randint(0, 21), 4, 4, 1)
    world_environment.generateFreeRoomContainer(4, 4, 0.5, 2)
    time_spend = time() - time_start

