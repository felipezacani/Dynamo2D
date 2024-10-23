cmake_minimum_required(VERSION 3.10)

# Project name
project(Dynamo2D C)

# Set the C standard
set(CMAKE_C_STANDARD 99)

# Specify the output directories for build
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Find SDL2 package
find_package(SDL2 REQUIRED)

# Include SDL2 headers
include_directories(${SDL2_INCLUDE_DIRS})

# Set the source folder
set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/source)

# Add the source files for your project
file(GLOB_RECURSE SOURCES "${SOURCE_DIR}/*.c")

# Add executable from source folder
add_executable(Dynamo2D ${SOURCES})

# Link the SDL2 library to your project
target_link_libraries(Dynamo2D ${SDL2_LIBRARIES})