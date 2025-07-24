cmake_minimum_required(VERSION 3.31)
project(Traffic_Simulator)

set(CMAKE_CXX_STANDARD 20)

add_executable(Traffic_Simulator main.cpp
        trafficlight.cpp
        trafficlight.h
        vehicle.cpp
        vehicle.h)
#Remember to add sfml functionality in here but DO NOT PUSH TO GITHUB, we'll upload every other file.
