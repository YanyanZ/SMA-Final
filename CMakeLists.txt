project(UTU-Bots C CXX)
cmake_minimum_required(VERSION 2.6)

set (CMAKE_CXX_FLAGS "-std=c++11 -g -Wall -Werror -Wno-unknown-pragmas")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/module/")

find_package(Boost 1.54 COMPONENTS filesystem system thread REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

add_subdirectory(src)
