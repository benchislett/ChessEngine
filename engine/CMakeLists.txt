cmake_minimum_required(VERSION 3.18.1)

project(ChessEngine)

set(CMAKE_BUILD_TYPE RelWithDebInfo)

include_directories(src)

file(GLOB SOURCES src/*.cpp)

add_executable(uciEngine ${SOURCES})