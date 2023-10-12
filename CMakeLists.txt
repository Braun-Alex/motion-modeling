cmake_minimum_required(VERSION 3.26)
project(motion_modeling)

set(CMAKE_CXX_STANDARD 23)
set(HEADERS crystal.h)
set(SOURCES crystal.cpp main.cpp)

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})
