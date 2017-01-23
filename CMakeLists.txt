cmake_minimum_required(VERSION 3.7)
project(voxels)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -O3")

find_package(GLFW REQUIRED)
find_package(OpenGL REQUIRED)
set(Boost_USE_STATIC_LIBS OFf)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.63.0 REQUIRED)

set(SOURCE_FILES
        vendors/linmath/linmath.h
        vendors/glad/glad.c
        src/main.cpp
        src/VoxelEngine.cpp src/VoxelEngine.hpp
        src/Game.cpp src/Game.hpp
        src/Window.cpp src/Window.hpp
        src/states/IGameState.hpp
        src/states/PlayState.cpp src/states/PlayState.hpp
        src/Timer.cpp src/Timer.hpp
        src/EventDispatcher.hpp
        src/utils/Hana.hpp
        src/events/MouseClickEvent.hpp
        src/events/KeyboardEvent.hpp
        src/events/MousePositionEvent.hpp
        src/opengl/Triangle.cpp src/opengl/Triangle.hpp
        src/opengl/OpenGLError.cpp src/opengl/OpenGLError.hpp
        src/opengl/Shader.cpp src/opengl/Shader.hpp
        src/opengl/Mesh.cpp src/opengl/Mesh.hpp
        src/opengl/Vertex.hpp
        src/opengl/Texture.cpp src/opengl/Texture.hpp
        vendors/stb_image/stb_image.hpp vendors/stb_image/stb_image.cpp src/opengl/TextureManager.cpp src/opengl/TextureManager.hpp src/opengl/IModel.hpp)

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

if (Hana_FOUND)
    include_directories(${Hana_INCLUDE_DIRS})
endif()

file(COPY src/shaders DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}.)
file(COPY resources DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}.)