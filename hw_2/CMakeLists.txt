cmake_minimum_required(VERSION 3.28)
project(hw_2)

set(CMAKE_CXX_STANDARD 20)

add_executable(hw_2
        include/person.h
        include/academic_subject.h
        include/parser.h
        include/pos_application_facade.h
        include/console_app.h

        src/main.cpp
        src/pos_application_facade.cpp
        src/academic_subject.cpp
        src/person.cpp
        src/console_app.cpp
        src/parser.cpp
        include/assessment_subject.h
        src/assessment_subject.cpp
)
