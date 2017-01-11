#ifndef VOXELS_WINDOW_HPP
#define VOXELS_WINDOW_HPP

#include <memory>
#include <cstdlib>
#include <stdexcept>
#include "../vendors/glad/glad.h"
#include "EventDispatcher.hpp"
#include <GLFW/glfw3.h>


struct DestroyglfwWin
{
    void operator()(GLFWwindow *ptr)
    {
        glfwDestroyWindow(ptr);
    }
};

using GLFWwindowPtr = std::unique_ptr<GLFWwindow, DestroyglfwWin>;

class Window
{
private:
    EventDispatcher &m_eventDispatcher;
    GLFWwindowPtr m_window;

public:
    Window(const int width, const int height, const char *title, EventDispatcher &ed);
    void pollEvents();
    bool isOpen();
    void swapBuffers();
    void closeWindow();
    void changeTitle(const char *title);
    void printGLInfos();
    /* event callbacks */
    void setupEventCallbacks();
    void onKeyboardEvent(int key, int scancode, int action, int mods);
    void onMouseButtonEvent(int button, int action, int mods);
    void onMouseScrollEvent(double xoffset, double yoffset);
    void onCursorPosEvent(double xpos, double ypos);
    ~Window();
};


#endif //VOXELS_WINDOW_HPP
