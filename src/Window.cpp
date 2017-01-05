#include "Window.hpp"

Window::Window(const int width, const int height, const char *title)
{
    // Initialise GLFW
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        throw std::runtime_error("Failed to initialize GLFW");
    }

    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    window = GLFWwindowPtr(glfwCreateWindow(width, height, title, nullptr, nullptr));

    if (window == nullptr) {
        fprintf(stderr, "Failed to open GLFW window.\n");
        glfwTerminate();
        throw std::runtime_error("Failed to open GLFW window.");
    }

    glfwMakeContextCurrent(window.get());
    // Glad openGL loader
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    glfwSwapInterval(1);

    // todo put that in a changeViewport function
    // Setting up viewport to draw inside
    int w, h;
    glfwGetFramebufferSize(window.get(), &w, &h);
    glViewport(0, 0, w, h);

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window.get(), GLFW_STICKY_KEYS, GL_TRUE);

    // Set the required callback functions
    // todo add a separated function
    // glfwSetKeyCallback(window, keyCallback);

    printf("Vendor:   %s\n", glGetString(GL_VENDOR));
    printf("Renderer: %s\n", glGetString(GL_RENDERER));
    printf("Version:  %s\n", glGetString(GL_VERSION));
    printf("GLSL:     %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
}

bool Window::isOpen()
{
    return !glfwWindowShouldClose(window.get());
}

void Window::pollEvents()
{
    glfwPollEvents();
}

void Window::swapBuffers()
{
    return glfwSwapBuffers(window.get());
}

void Window::closeWindow()
{
    glfwSetWindowShouldClose(window.get(), 1);
}

Window::~Window()
{
    glfwTerminate();
}
