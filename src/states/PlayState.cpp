#include "PlayState.hpp"

PlayState::PlayState(Game &game) : IGameState(game)
, m_model({
                  0.5f,  0.5f, 0.0f,  // Top Right
                  0.5f, -0.5f, 0.0f,  // Bottom Right
                  -0.5f, -0.5f, 0.0f,  // Bottom Left
                  -0.5f,  0.5f, 0.0f   // Top Left
          })
{
    // events handling
    EventDispatcher &eventDispatcher = game.getEventDispatcherRef();

    eventDispatcher.subscribe([this](MouseClickEvent e) {
        mouseClickEventHandle(e);
    });

    eventDispatcher.subscribe([this](MousePositionEvent e) {
        mousePositionEventHandle(e);
    });

    eventDispatcher.subscribe([this](KeyboardEvent e) {
        keyboardEventHandle(e);
    });
}

void PlayState::mouseClickEventHandle(MouseClickEvent e)
{
    std::cout << "Mouse\n";
}

void PlayState::mousePositionEventHandle(MousePositionEvent e)
{
    // std::cout << "Mouse move\n";
}

void PlayState::keyboardEventHandle(KeyboardEvent e)
{
    auto window = m_game.getWindowRef().get();

    switch (e.m_key) {
        case GLFW_KEY_ESCAPE:
            window->closeWindow();
            break;
        default:
            break;
    }
}


void PlayState::update(const float dt)
{

}

void PlayState::draw(const float dt)
{
    // rendering here..
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    m_model.draw();
}

PlayState::~PlayState()
{
    std::cout << "playstate deallocated\n";
    m_sigConnection.disconnect();
}
