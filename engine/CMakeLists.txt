cmake_minimum_required(VERSION 3.18.1)

project(ChessEngine)

include_directories(src)

file(GLOB SOURCES src/*.cpp)

add_executable(uciEngine ${SOURCES})