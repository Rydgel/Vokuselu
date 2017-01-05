#ifndef VOXELS_WINDOW_HPP
#define VOXELS_WINDOW_HPP

#include <memory>
#include <cstdlib>
#include <stdexcept>
#include "../vendors/glad/glad.h"
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
    GLFWwindowPtr window;

public:
    Window(const int width, const int height, const char *title);
    void pollEvents();
    bool isOpen();
    void swapBuffers();
    void closeWindow();
    void changeTitle(const char *title);
    ~Window();
};


#endif //VOXELS_WINDOW_HPP
