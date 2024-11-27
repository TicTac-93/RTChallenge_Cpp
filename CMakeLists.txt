cmake_minimum_required(VERSION 3.5.0)
project(RTChallenge VERSION 0.1.0 LANGUAGES C CXX)

add_executable(UNIT_TEST src/tests/test_001-a.cpp)

add_subdirectory(src/lib)
target_link_libraries(UNIT_TEST PUBLIC
                      RT_Datatypes)
target_include_directories(UNIT_TEST PUBLIC
                           "../lib")

#include(CTest)
enable_testing()

