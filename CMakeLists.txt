cmake_minimum_required(VERSION 3.5)
project(DataStructureAlgorithms)

set(CMAKE_CXX_FLAGS "-std=c++14 -Wall")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

ADD_DEFINITIONS(-DUNICODE)
ADD_DEFINITIONS(-D_UNICODE)

include_directories( DataStructuresAlgorithms )

# Testing
set(LIBRARIES_DIRECTORY libraries)
add_subdirectory(${LIBRARIES_DIRECTORY}/googletest)

enable_testing()

include_directories( ${gtest_SOURCE_DIR}/include )

file(GLOB_RECURSE TEST_SOURCES DataStructuresAlgorithmsTests/*.cpp DataStructuresAlgorithmsTests/*.hpp)
add_executable(DataStructuresAlgorithmsTests ${TEST_SOURCES})

target_link_libraries(DataStructuresAlgorithmsTests gtest gtest_main)
