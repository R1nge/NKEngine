cmake_minimum_required(VERSION 4.0)
project(NKEngine)

find_package(SDL2 REQUIRED)
include_directories(SDL2Test ${SDL2_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 20)

add_executable(NKEngine main.cpp)
target_link_libraries(NKEngine ${SDL2_LIBRARIES})
