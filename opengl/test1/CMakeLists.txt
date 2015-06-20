project(test1)

cmake_minimum_required(VERSION 2.8)

file(GLOB SOURCES *.cpp)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(Boost 1.58.0 COMPONENTS system filesystem REQUIRED)

set(SHADER_DIRECTORY ${CMAKE_INSTALL_PREFIX}/shader)

set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS "-Wall -Werror -pedantic ${CMAKE_CXX_FLAGS}")

include_directories(${SDL2_INCLUDE_DIR})
include_directories(${OPENGL_INCLUDE_DIR})
include_directories(${GLEW_INCLUDE_DIR})
include_directories(${Boost_INCLUDE_DIRS})

add_executable(main ${SOURCES})
set_target_properties(main PROPERTIES
                      COMPILE_DEFINITIONS SHADER_DIRECTORY="${SHADER_DIRECTORY}")
target_link_libraries(main ${SDL2_LIBRARY} ${OPENGL_LIBRARIES} ${GLEW_LIBRARY} ${Boost_LIBRARIES})

install(TARGETS main DESTINATION ${CMAKE_INSTALL_PREFIX})
install(DIRECTORY shader/ DESTINATION ${SHADER_DIRECTORY}
        PATTERN "shader/*.glsl")
