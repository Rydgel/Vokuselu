#include "PlayState.hpp"

PlayState::PlayState(Game &game) : IGameState(game)
, m_camera(game.getEventDispatcherRef())
, m_model(game.getTextureManagerRef())
{
    // events handling
    EventDispatcher &eventDispatcher = game.getEventDispatcherRef();
    // events callbacks
    eventDispatcher.subscribe([this](MouseClickEvent e) { mouseClickEventHandle(e); });
    eventDispatcher.subscribe([this](MousePositionEvent e) { mousePositionEventHandle(e); });
    eventDispatcher.subscribe([this](KeyboardEvent e) { keyboardEventHandle(e); });
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
    m_camera.update(dt);
}

void PlayState::draw(const float dt)
{
    // rendering here..
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // LirikN cubes
    glm::vec3 cubePositions[] = {
            glm::vec3( 0.0f,  0.0f,  0.0f),
            glm::vec3( 2.0f,  5.0f, -15.0f),
            glm::vec3(-1.5f, -2.2f, -2.5f),
            glm::vec3(-3.8f, -2.0f, -12.3f),
            glm::vec3( 2.4f, -0.4f, -3.5f),
            glm::vec3(-1.7f,  3.0f, -7.5f),
            glm::vec3( 1.3f, -2.0f, -2.5f),
            glm::vec3( 1.5f,  2.0f, -2.5f),
            glm::vec3( 1.5f,  0.2f, -1.5f),
            glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    glm::mat4 view;
    view = m_camera.getViewMatrix();
    glm::mat4 projection;
    projection = glm::perspective(m_camera.m_zoom, 800.0f / 600.0f, 0.1f, 1000.0f);

    int i = 0;
    for (auto cubePosition : cubePositions) {
        glm::mat4 model;
        model = glm::translate(model, cubePosition);
        GLfloat angle = 0;
        model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));
        i++;
        m_model.draw(view, model, projection);
    }
}

PlayState::~PlayState()
{
    std::cout << "playstate deallocated\n";
    m_sigConnection.disconnect();
}
