cmake_minimum_required(VERSION 3.18.1)

project(ChessEngine)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(src uci)

file(GLOB SOURCES src/*.cpp)

add_library(engine OBJECT ${SOURCES})

file(GLOB UCI_SOURCES uci/*.cpp)

add_executable(uciInterface ${UCI_SOURCES})
target_link_libraries(uciInterface PRIVATE engine)

find_package(Catch2 REQUIRED)

file(GLOB TEST_SOURCES test/*.cpp)

add_executable(test ${SOURCES} ${TEST_SOURCES})
target_link_libraries(test Catch2::Catch2)
# target_link_libraries(test engine)
