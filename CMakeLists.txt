cmake_minimum_required(VERSION 3.28)
project(untitled)

set(CMAKE_CXX_STANDARD 17)

add_executable(untitled main.cpp)
# Add the RapidXML library
add_library(rapidxml INTERFACE)
target_include_directories(rapidxml INTERFACE ~/ClionProjects/untitled/libs)
add_executable(stvuln ...)
target_link_libraries(stvuln rapidxml)


