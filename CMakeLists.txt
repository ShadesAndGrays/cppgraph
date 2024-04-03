cmake_minimum_required(VERSION 3.14)

project(cgraph CXX)

set(src
src/main.cpp
src/graph/graph.cpp
)

add_executable(cgraph ${src})

find_package(fmt)
find_package(raylib)

target_link_libraries(${PROJECT_NAME} fmt::fmt raylib)
