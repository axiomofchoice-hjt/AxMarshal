cmake_minimum_required(VERSION 3.9)

project(axm)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_NAME}_SRCS)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${PROJECT_NAME} ${${PROJECT_NAME}_SRCS})
add_compile_options(-Wall)

include(GNUInstallDirs)