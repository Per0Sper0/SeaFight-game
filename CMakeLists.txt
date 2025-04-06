cmake_minimum_required(VERSION 3.0)

project(SeaFight)

set(curdir ${CMAKE_CURRENT_SOURCE_DIR})

include_directories(./)

find_package(SFML 2.5.1 COMPONENTS graphics window system REQUIRED)

add_executable(main main.cpp)

add_library(project Field.cpp Player.cpp)

file(COPY asserts DESTINATION ${CMAKE_BINARY_DIR})

target_link_libraries(main project sfml-graphics sfml-window sfml-system project)