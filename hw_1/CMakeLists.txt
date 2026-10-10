cmake_minimum_required(VERSION 3.28)
project(hw_1)

set(CMAKE_CXX_STANDARD 23)

add_executable(hw_1
        includes/Park.h
        includes/ObjectPark.h
        includes/OwnerPark.h

        src/main.cpp
        src/OwnerPark.cpp
        includes/ServiceCenter.h
        includes/CreatorObject.h
        src/Park.cpp
        src/ObjectPark.cpp
        src/CreatorObject.cpp
)