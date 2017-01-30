#include "Game.hpp"

Game::Game()
{
    m_window = std::make_unique<Window>(m_windowWidth, m_windowHeight, m_windowTitle, m_eventDispatcher);
    m_timer.init();
    // load textures
    m_textureArray.addTextures(
            {
                    "resources/textures/blocks/grass_side.png",
                    "resources/textures/blocks/dirt.png",
                    "resources/textures/blocks/wool_colored_green.png",
                    "resources/textures/blocks/dirt.png",
                    "resources/textures/blocks/dirt.png",
                    "resources/textures/blocks/dirt.png",
                    "resources/textures/blocks/stone.png",
                    "resources/textures/blocks/stone.png",
                    "resources/textures/blocks/stone.png",
            }
    );
}

void Game::pushState(GameStatePtr state)
{
    m_states.push(std::move(state));
}

void Game::popState()
{
    m_states.pop();
}

void Game::changeState(GameStatePtr state)
{
    if (!m_states.empty())
        popState();
    pushState(std::move(state));
}

const boost::optional<GameStatePtr&> Game::peekState()
{
    if (m_states.empty())
        return boost::none;
    return boost::make_optional<GameStatePtr&>(m_states.top());
}

void Game::gameLoop()
{
    while (m_window->isOpen())
    {
        const float dt = m_timer.getDelta();

        // Check and call events
        m_window->pollEvents();

        auto &currentState = peekState();
        if (!currentState.is_initialized())
            continue;
        /* Update game and timer UPS */
        currentState.get()->update(dt);
        m_timer.updateUPS();
        /* Render game and update timer FPS */
        currentState.get()->draw(dt);
        m_timer.updateFPS();

        /* Update timer */
        m_timer.update();

        // display fps
        std::ostringstream out;
        out << "LearnOpenGL • FPS: " << m_timer.getFPS() << " | UPS: " << m_timer.getUPS();
        m_window->changeTitle(out.str().c_str());

        // Swap the buffers
        m_window->swapBuffers();
    }
}

EventDispatcher &Game::getEventDispatcherRef()
{
    return m_eventDispatcher;
}

WindowPtr &Game::getWindowRef()
{
    return m_window;
}

TextureArray &Game::getTextureArrayRef()
{
    return m_textureArray;
}

Game::~Game()
{
    while (!m_states.empty())
        popState();
    m_window->closeWindow();
}