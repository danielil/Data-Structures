cmake_minimum_required(VERSION 3.2)
project(DataStructureAlgorithms)

set(CMAKE_CXX_FLAGS "-std=c++14 -Wall")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

ADD_DEFINITIONS(-DUNICODE)
ADD_DEFINITIONS(-D_UNICODE)

include_directories( DataStructuresAlgorithms )

# Includes Catch in the project:
set(EXT_PROJECTS_DIR ext)
add_subdirectory(${EXT_PROJECTS_DIR}/catch)
include_directories(${CATCH_INCLUDE_DIR} ${COMMON_INCLUDES})
enable_testing(true)  # Enables unit-testing.

file(GLOB_RECURSE TEST_SOURCES DataStructuresAlgorithmsTests/*.cpp DataStructuresAlgorithmsTests/*.hpp)
add_executable(DataStructuresAlgorithmsTests ${TEST_SOURCES})

