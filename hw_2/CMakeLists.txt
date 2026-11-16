cmake_minimum_required(VERSION 3.20)
project(hw_2 CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(pos_domain src/final_score.cpp src/academic_subject.cpp
    src/assessment_subject.cpp src/person.cpp)
target_include_directories(pos_domain PUBLIC include)
add_library(pos_application src/pos_application_facade.cpp src/application/reporting.cpp)
target_link_libraries(pos_application PUBLIC pos_domain)
add_library(pos_adapters src/repository.cpp src/parser.cpp src/console_app.cpp
    src/adapters/legacy_facade_console.cpp src/adapters/reporting_console.cpp
    src/adapters/csv_final_exporter.cpp)
target_link_libraries(pos_adapters PUBLIC pos_application)
add_library(core src/bootstrap/application_container.cpp)
target_link_libraries(core PUBLIC pos_adapters)
add_executable(hw_2 src/main.cpp)
target_link_libraries(hw_2 PRIVATE core)

include(CTest)
if(BUILD_TESTING)
    include(FetchContent)
    FetchContent_Declare(Catch2 GIT_REPOSITORY https://github.com/catchorg/Catch2.git GIT_TAG v3.5.2)
    FetchContent_MakeAvailable(Catch2)
    add_executable(unit_tests tests/test.cpp)
    target_link_libraries(unit_tests PRIVATE core Catch2::Catch2WithMain)
    add_test(NAME unit_tests COMMAND unit_tests)
endif()
