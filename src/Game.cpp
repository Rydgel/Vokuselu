#include "Game.hpp"

Game::Game()
{
    window = WindowPtr(new Window(windowWidth, windowHeight, windowTitle));
}

void Game::pushState(GameStatePtr state)
{
    states.push(std::move(state));
}

void Game::popState()
{
    states.pop();
}

void Game::changeState(GameStatePtr state)
{
    if (!states.empty())
        popState();
    pushState(std::move(state));
}

const boost::optional<GameStatePtr&> Game::peekState()
{
    if (states.empty())
        return boost::none;
    return boost::make_optional<GameStatePtr&>(states.top());
}

void Game::gameLoop()
{
    // todo events management
    while (window->isOpen())
    {
        // Check and call events
        window->pollEvents();

        // todo get delta from each loop
        const float dt = 0.0;

        auto &currentState = peekState();
        if (!currentState.is_initialized()) break;
        currentState.get()->handleInput(dt);
        currentState.get()->update(dt);
        currentState.get()->draw(dt);

        // Swap the buffers
        window->swapBuffers();
    }
}

Game::~Game()
{
    while (!states.empty())
        popState();
    window->closeWindow();
}