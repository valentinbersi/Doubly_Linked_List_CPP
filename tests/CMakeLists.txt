cmake_minimum_required(VERSION 3.22)
project(DLList_Tests)

set(CMAKE_C_STANDARD 23)

add_subdirectory(gtest_lib)

include_directories(../)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(Google_Tests_run
        DLList_tests.cpp
)

target_link_libraries(Google_Tests_run gtest gtest_main)