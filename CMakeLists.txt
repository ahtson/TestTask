cmake_minimum_required(VERSION 3.20)

project(Test_Assignment_for_Dima_Trushin VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${CMAKE_SOURCE_DIR})

add_executable(test_vector test.cpp)

find_package(Catch2 REQUIRED)
target_link_libraries(test_vector PRIVATE Catch2::Catch2WithMain)

include(CTest)
include(Catch)

catch_discover_tests(test_vector)
