cmake_minimum_required(VERSION 3.12)
project(maze)

set(CMAKE_CXX_STANDARD 11)

add_executable(maze main.cpp maze.cpp maze.h game.cpp game.h)