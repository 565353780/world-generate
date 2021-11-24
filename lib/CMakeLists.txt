cmake_minimum_required(VERSION 3.0)

project(WorldEnvironment)

set(CMAKE_CXX_STANDARD 17)

add_compile_definitions(EXPORT_PYBIND)

set(WORLD_ENVIRONMENT_DIR ${PROJECT_SOURCE_DIR}/../src/WorldEnvironment)

file(GLOB_RECURSE SOURCES ${WORLD_ENVIRONMENT_DIR}/*.cpp)
file(GLOB_RECURSE HEADERS ${WORLD_ENVIRONMENT_DIR}/*.h)

include_directories(
    /usr/include
    /usr/include/python3.8
    ${PROJECT_SOURCE_DIR}
    ${WORLD_ENVIRONMENT_DIR}
    ${WORLD_ENVIRONMENT_DIR}/EasyShape
    ${WORLD_ENVIRONMENT_DIR}/EasyWorld
)

# add_library(${PROJECT_NAME} SHARED ${SOURCES})

find_package(pybind11 REQUIRED)
pybind11_add_module(WorldEnvironment ${SOURCES})

