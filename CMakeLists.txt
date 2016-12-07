# Daniel Sebastian Iliescu, http://dansil.net
# MIT License (MIT), http://opensource.org/licenses/MIT

cmake_minimum_required( VERSION 3.2 )

project( DataStructuresAlgorithms CXX )

# Create the tester executable given the test source directory
set( TEST_DIRECTORY Tests )
set( TEST_NAME ${PROJECT_NAME}${TEST_DIRECTORY} )
file( GLOB_RECURSE TEST_SOURCES ${TEST_DIRECTORY}/*.cpp )
add_executable( ${TEST_NAME} ${TEST_SOURCES} )

# Include the source headers
set( SOURCE_HEADERS Sources/Includes )
target_include_directories(
	${TEST_NAME}
	PUBLIC ${SOURCE_HEADERS} )

# Include the external headers
set( EXTERNAL_HEADERS External/Includes )
target_include_directories(
	${TEST_NAME}
	PUBLIC ${EXTERNAL_HEADERS} )

# Enforce C++14 standard
set( CMAKE_CXX_STANDARD 14 )
set( CMAKE_CXX_STANDARD_REQUIRED on )

# Additional compiler options
set( CLANG_GNU_COMPILER_OPTIONS "-Wall" "-Wextra" "-Werror" "-Wshadow" "-Wnon-virtual-dtor" "-pedantic" )
set( MSVC_COMPILER_OPTIONS "/W4" "/WX" )

if ( CMAKE_CXX_COMPILER_ID MATCHES Clang OR
	 CMAKE_CXX_COMPILER_ID MATCHES GNU )
	target_compile_options(
		${TEST_NAME}
		PUBLIC ${CLANG_GNU_COMPILER_OPTIONS} )
elseif( CMAKE_CXX_COMPILER_ID MATCHES MSVC )
	target_compile_options(
		${TEST_NAME}
		PUBLIC ${MSVC_COMPILER_OPTIONS} )
endif()

# Specifying output settings
set_target_properties(
	${TEST_NAME}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )