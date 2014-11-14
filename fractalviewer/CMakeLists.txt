cmake_minimum_required(VERSION 2.6)

project(fractal_viewer)

set(Fractal_viewer_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")

file(GLOB fractal_viewer_sources "${Fractal_viewer_SOURCE_DIR}/*.java")
find_package(Java REQUIRED)
include(UseJava)

set(CMAKE_JAVA_COMPILE_FLAGS "-source" "7") # "-target" "7")

add_jar(
	fractal_viewer
	SOURCES ${fractal_viewer_sources}
	OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/jar
	)


