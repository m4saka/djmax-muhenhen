cmake_minimum_required(VERSION 2.8)
project(djmax_muhenhen CXX)
set(CMAKE_CXX_STANDARD 17)
include_directories(include)
file(GLOB_RECURSE sources
    ${PROJECT_SOURCE_DIR}/src/*.cpp)
add_executable(djmax_muhenhen ${sources})
