#include "Game.hpp"

Game::Game()
{
    window = std::unique_ptr<Window>(
            new Window(windowWidth, windowHeight, windowTitle)
    );
}

void Game::gameLoop()
{
    // todo events management
    while (window->isOpen())
    {
        // Check and call events
        window->pollEvents();

        // rendering here..
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Swap the buffers
        window->swapBuffers();
    }
}

Game::~Game()
{
    window->closeWindow();
}