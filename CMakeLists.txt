cmake_minimum_required(VERSION 3.9)

project(AxMarshal VERSION 0.1.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(axm)
add_subdirectory(axmc)
add_subdirectory(test)