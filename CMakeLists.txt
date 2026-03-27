cmake_minimum_required(VERSION 3.10)
project(darbas1 VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES main.cpp utils.cpp student.cpp)

include_directories(${CMAKE_SOURCE_DIR})

add_executable(darbas1 ${SOURCES})