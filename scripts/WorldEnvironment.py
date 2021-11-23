#!/usr/bin/env python
# -*- coding: utf-8 -*-

import ctypes
world_environment_so = ctypes.CDLL('../lib/libWorldEnvironment.so')

WorldEnvironment = world_environment_so.WorldEnvironment()

print("load world_environment_so success!")

