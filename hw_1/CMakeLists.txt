cmake_minimum_required(VERSION 3.28)
project(hw_1)

set(CMAKE_CXX_STANDARD 23)

add_executable(hw_1
        src/main.cpp

        includes/Park.h
        includes/ObjectPark.h
        includes/OwnerPark.h
        includes/StorageCenter.h
        includes/CreatorObject.h
        includes/ServiceCenter.h
        includes/DIContainer.h

        src/OwnerPark.cpp
        src/StorageCenter.cpp
        src/Park.cpp
        src/ObjectPark.cpp
        src/CreatorObject.cpp
        src/ServiceCenter.cpp
)

add_executable(run_test
        tests/test.cpp

        includes/Park.h
        includes/ObjectPark.h
        includes/OwnerPark.h
        includes/DIContainer.h
        includes/StorageCenter.h
        includes/CreatorObject.h
        includes/ServiceCenter.h

        src/OwnerPark.cpp
        src/StorageCenter.cpp
        src/Park.cpp
        src/ObjectPark.cpp
        src/CreatorObject.cpp
        src/ServiceCenter.cpp
)