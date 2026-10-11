cmake_minimum_required(VERSION 3.28)
project(hw_1)

set(CMAKE_CXX_STANDARD 23)

add_executable(hw_1
        includes/Park.h
        includes/ObjectPark.h
        includes/OwnerPark.h
        includes/StorageCenter.h
        includes/CreatorObject.h

        src/main.cpp
        src/OwnerPark.cpp
        src/Park.cpp
        src/ObjectPark.cpp
        src/CreatorObject.cpp
        src/StorageCenter.cpp
)

add_executable(run_test
        includes/Park.h
        includes/ObjectPark.h
        includes/OwnerPark.h
        includes/StorageCenter.h
        includes/CreatorObject.h

        tests/test.cpp
        src/OwnerPark.cpp
        src/StorageCenter.cpp
        src/Park.cpp
        src/ObjectPark.cpp
        src/CreatorObject.cpp
)