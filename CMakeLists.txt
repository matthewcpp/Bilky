cmake_minimum_required(VERSION 3.0)

project(Bilky CXX)

#Use solution folders.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)


if (${CMAKE_CXX_COMPILER_ID} STREQUAL GNU)
	SET(GCC_COMPILE_FLAGS "-std=c++11")
	add_definitions(${GCC_COMPILE_FLAGS})
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)