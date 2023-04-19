cmake_minimum_required(VERSION 3.9)

project(axmc)

aux_source_directory(. ${PROJECT_NAME}_SRCS)
aux_source_directory(File ${PROJECT_NAME}_SRCS)
aux_source_directory(FrontEnd ${PROJECT_NAME}_SRCS)
aux_source_directory(BackEnd ${PROJECT_NAME}_SRCS)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_SRCS})

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -g)

find_package(inja CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE pantor::inja)

find_package(fmt CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt-header-only)

find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)
set(nlohmann-json_IMPLICIT_CONVERSIONS OFF)