cmake_minimum_required(VERSION 3.7)
project(voxels)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -O3")

find_package(GLFW REQUIRED)
find_package(OpenGL REQUIRED)

set(SOURCE_FILES vendors/glad/glad.c src/main.cpp vendors/linmath/linmath.h)
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

file(COPY src/shaders DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}.)