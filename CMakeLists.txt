#[[ ggr2glsl
 [[ Copyright (C) 2021 Erik Präntare
 [[
 [[ This program is free software: you can redistribute it and/or modify
 [[ it under the terms of the GNU Affero General Public License as published by
 [[ the Free Software Foundation, either version 3 of the License, or
 [[ (at your option) any later version.
 [[ 
 [[ This program is distributed in the hope that it will be useful,
 [[ but WITHOUT ANY WARRANTY; without even the implied warranty of
 [[ MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 [[ GNU Affero General Public License for more details.
 [[ 
 [[ You should have received a copy of the GNU Affero General Public License
 [[ along with this program.  If not, see <http://www.gnu.org/licenses/>.
#]]

#---------------------------CMake Project Config-------------------------------
project(ggr2glsl LANGUAGES CXX)
cmake_minimum_required(VERSION 3.12)

add_executable(ggr2glsl
    src/main.cpp
    src/color.cpp
    src/segment.cpp)

set_target_properties(ggr2glsl
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED TRUE)

if(MINGW)
    target_link_libraries(ggr2glsl PRIVATE -static)
endif()

#---------------------------Compilation database generation--------------------
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_custom_target(copy-compile-commands ALL
    ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_BINARY_DIR}/compile_commands.json
        ${PROJECT_SOURCE_DIR}/compile_commands.json)
