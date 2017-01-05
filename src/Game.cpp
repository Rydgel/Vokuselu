#include "Game.hpp"

Game::Game()
{
    window = std::make_unique<Window>(windowWidth, windowHeight, windowTitle);
    timer.init();
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
        const float dt = timer.getDelta();

        // Check and call events
        window->pollEvents();

        auto &currentState = peekState();
        if (!currentState.is_initialized()) break;
        /* Handle input */
        currentState.get()->handleInput(dt);
        /* Update game and timer UPS */
        currentState.get()->update(dt);
        timer.updateUPS();
        /* Render game and update timer FPS */
        currentState.get()->draw(dt);
        timer.updateFPS();

        /* Update timer */
        timer.update();

        // display fps
        std::ostringstream out;
        out << "LearnOpenGL • FPS: " << timer.getFPS() << " | UPS: " << timer.getUPS();
        window->changeTitle(out.str().c_str());

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