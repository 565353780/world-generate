cmake_minimum_required(VERSION 3.0)

project(WorldEnvironment)

set(CMAKE_CXX_STANDARD 17)

add_compile_definitions(EXPORT_PYBIND)

set(UNIT_WORLD_ENVIRONMENT_DIR ${PROJECT_SOURCE_DIR}/../src/WorldEnvironment)

file(GLOB_RECURSE SOURCES ${UNIT_WORLD_ENVIRONMENT_DIR}/*.cpp)
file(GLOB_RECURSE HEADERS ${UNIT_WORLD_ENVIRONMENT_DIR}/*.h)

include_directories(
    /usr/include
    /usr/include/python3.8
    ${PROJECT_SOURCE_DIR}
    ${UNIT_WORLD_ENVIRONMENT_DIR}
    ${UNIT_WORLD_ENVIRONMENT_DIR}/EasyShape
    ${UNIT_WORLD_ENVIRONMENT_DIR}/EasyWorld
    ${UNIT_WORLD_ENVIRONMENT_DIR}/UnitWorld
)

# add_library(${PROJECT_NAME}Lib SHARED ${SOURCES})

find_package(pybind11 REQUIRED)
pybind11_add_module(UnitWorldEnvironment ${SOURCES})

