#include "Window.hpp"

Window::Window(const int width, const int height, const char *title, EventDispatcher &ed)
: m_eventDispatcher(ed)
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
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    m_window = GLFWwindowPtr(glfwCreateWindow(width, height, title, nullptr, nullptr));

    if (m_window == nullptr) {
        fprintf(stderr, "Failed to open GLFW window.\n");
        glfwTerminate();
        throw std::runtime_error("Failed to open GLFW window.");
    }

    glfwMakeContextCurrent(m_window.get());
    glfwSwapInterval(0);
    // Glad openGL loader
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

    // todo put that in a changeViewport function
    // Setting up viewport to draw inside
    int w, h;
    glfwGetFramebufferSize(m_window.get(), &w, &h);
    glViewport(0, 0, w, h);

    // Set the required callback functions
    setupEventCallbacks();
    printGLInfos();
}

bool Window::isOpen()
{
    return !glfwWindowShouldClose(m_window.get());
}

void Window::pollEvents()
{
    glfwPollEvents();
    // Mouse position
    double xpos, ypos;
    glfwGetCursorPos(m_window.get(), &xpos, &ypos);
    Event mousePosE = MousePositionEvent(xpos, ypos);
    m_eventDispatcher.push(mousePosE);
}

void Window::swapBuffers()
{
    return glfwSwapBuffers(m_window.get());
}

void Window::closeWindow()
{
    glfwSetWindowShouldClose(m_window.get(), 1);
}

void Window::changeTitle(const char *title)
{
    glfwSetWindowTitle(m_window.get(), title);
}

void Window::printGLInfos()
{
    printf("Vendor:   %s\n", glGetString(GL_VENDOR));
    printf("Renderer: %s\n", glGetString(GL_RENDERER));
    printf("Version:  %s\n", glGetString(GL_VERSION));
    printf("GLSL:     %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
}

void Window::setupEventCallbacks()
{
    auto windowRawPtr = m_window.get();

    // todo try to see if it's really needed
    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(windowRawPtr, GLFW_STICKY_KEYS, GL_TRUE);

    glfwSetWindowUserPointer(windowRawPtr, this);

    glfwSetKeyCallback(windowRawPtr, (GLFWkeyfun) [](auto glfwWindow, auto... params) {
        auto window = static_cast<Window *>(glfwGetWindowUserPointer(glfwWindow));
        window->onKeyboardEvent(params...);
    });

    glfwSetMouseButtonCallback(windowRawPtr, (GLFWmousebuttonfun) [](auto glfwWindow, auto... params) {
        auto window = static_cast<Window *>(glfwGetWindowUserPointer(glfwWindow));
        window->onMouseButtonEvent(params...);
    });

    glfwSetScrollCallback(windowRawPtr, (GLFWscrollfun) [](auto glfwWindow, auto... params) {
        auto window = static_cast<Window *>(glfwGetWindowUserPointer(glfwWindow));
        window->onMouseScrollEvent(params...);
    });
}

void Window::onKeyboardEvent(int key, int scancode, int action, int mods)
{
    Event e = KeyboardEvent(key, scancode, action, mods);
    m_eventDispatcher.push(e);
}

void Window::onMouseButtonEvent(int button, int action, int mods)
{
    Event e = MouseClickEvent(button, action, mods);
    m_eventDispatcher.push(e);
}

void Window::onMouseScrollEvent(double xoffset, double yoffset)
{
    // printf("SCROLL LUL\n");
}

Window::~Window()
{
    glfwTerminate();
}
