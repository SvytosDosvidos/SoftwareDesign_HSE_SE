cmake_minimum_required(VERSION 3.28)
project(hw_2)

set(CMAKE_CXX_STANDARD 20)

add_executable(hw_2 src/main.cpp
        include/person.h
        include/academic_subject.h
        include/parser.h
        src/person.cpp
        include/console_controller.h
        src/console_controller.cpp
        include/pos_application_facade.h
        src/pos_application_facade.cpp
        src/academic_subject.cpp
)
