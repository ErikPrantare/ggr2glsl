cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 17)

project(ggr2glsl LANGUAGES CXX)

add_executable(ggr2glsl
    src/main.cpp
    src/color.cpp
    src/segment.cpp)

if(MINGW)
    target_link_libraries(ggr2glsl PRIVATE -static)
endif()
