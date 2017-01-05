cmake_minimum_required(VERSION 3.7)
project(voxels)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -O3")

find_package(GLFW REQUIRED)
find_package(OpenGL REQUIRED)
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME ON)
find_package(Boost 1.63.0 REQUIRED)

set(SOURCE_FILES
        vendors/linmath/linmath.h
        vendors/glad/glad.c
        src/main.cpp
        src/VoxelEngine.cpp src/VoxelEngine.hpp
        src/Game.cpp src/Game.hpp
        src/Window.cpp src/Window.hpp
        src/GameState.hpp
        src/PlayState.cpp src/PlayState.hpp)

add_executable(voxels ${SOURCE_FILES})

if (OPENGL_FOUND)
    include_directories(${OPENGL_INCLUDE_DIR})
    target_link_libraries(voxels ${OPENGL_gl_LIBRARY})
endif()

if (GLFW_FOUND)
    include_directories(${GLFW_INCLUDE_DIR})
    target_link_libraries(voxels ${GLFW_LIBRARIES})
endif()

if (GLM_FOUND)
    include_directories(${GLM_INCLUDE_DIR})
endif()

if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    target_link_libraries(voxels ${Boost_LIBRARIES})
endif()

file(COPY src/shaders DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}.)