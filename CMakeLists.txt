cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 20)

project(ggr2glsl LANGUAGES CXX)

add_executable(ggr2glsl
    src/main.cpp
    src/color.cpp
    src/segment.cpp)
