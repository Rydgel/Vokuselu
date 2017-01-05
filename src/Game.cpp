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
        /*const float dt = tmr.elapsed();
        tmr.reset();

        // show FPS
        // printf("current frame time: %f\n", dt);
        // printf("fps: %f\n", 1 / (dt / 1000));
        std::ostringstream out;
        out << "LearnOpenGL: (" << round(1 / (dt / 1000)) << ") fps";
        window->changeTitle(out.str().c_str());*/

        // Check and call events
        const float dt = timer.getDelta();
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