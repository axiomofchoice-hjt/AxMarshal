cmake_minimum_required(VERSION 3.9)

project(axm)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_NAME}_SRCS)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(${PROJECT_NAME} ${${PROJECT_NAME}_SRCS})

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -g)

find_package(RapidJSON CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE rapidjson)

# include(GNUInstallDirs)