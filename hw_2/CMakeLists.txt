cmake_minimum_required(VERSION 3.20)
project(hw_2 CXX)

set(CMAKE_CXX_STANDARD 20)

add_library(core
        src/academic_subject.cpp
        src/assessment_subject.cpp
        src/person.cpp
        src/parser.cpp
        src/pos_application_facade.cpp
        src/console_app.cpp
        include/repository.h
        src/repository.cpp
)

target_include_directories(core PUBLIC include)

add_executable(hw_2 src/main.cpp)
target_link_libraries(hw_2 PRIVATE core)

include(FetchContent)
FetchContent_Declare(Catch2 GIT_REPOSITORY https://github.com/catchorg/Catch2.git GIT_TAG v3.5.2)
FetchContent_MakeAvailable(Catch2)

add_executable(unit_tests tests/test.cpp)
target_link_libraries(unit_tests PRIVATE core Catch2::Catch2WithMain)