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

class Window
{
private:
    std::unique_ptr<GLFWwindow, DestroyglfwWin> window;

public:
    Window(const int width, const int height, const char *title);
    void pollEvents();
    int isOpen();
    void swapBuffers();
    void closeWindow();
    ~Window();
};


#endif //VOXELS_WINDOW_HPP
