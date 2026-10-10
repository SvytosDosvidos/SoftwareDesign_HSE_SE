cmake_minimum_required(VERSION 3.28)
project(hw_1)

set(CMAKE_CXX_STANDARD 14)

add_executable(hw_1
        src/main.cpp
        includes/Park.h
        includes/ObjectPark.h
        includes/OwnerPark.h
        src/OwnerPark.cpp
)
