cmake_minimum_required(VERSION 3.28)
project(hw_1)

set(CMAKE_CXX_STANDARD 20)

add_executable(hw_1
        includes/Park.h
        includes/ObjectPark.h
        includes/OwnerPark.h

        src/main.cpp
        src/OwnerPark.cpp
)