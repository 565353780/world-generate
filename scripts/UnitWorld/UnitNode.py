#!/usr/bin/env python
# -*- coding: utf-8 -*-

from shapely.geometry import Polygon
from treelib import Tree

class UnitNode:
    def __init__(self):
        self.name = None
        self.id = None
        self.type = None
        self.boundary_polygon = None
        return


