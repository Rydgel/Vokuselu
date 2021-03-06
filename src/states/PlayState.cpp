#include "PlayState.hpp"

PlayState::PlayState(Game &game) : IGameState(game)
, m_camera(game.getEventDispatcherRef())
, m_model(game.getTextureArrayRef())
, m_world(game)
{
    // events handling
    EventDispatcher &eventDispatcher = game.getEventDispatcherRef();
    // events callbacks
    eventDispatcher.subscribe([this](MouseClickEvent e) { mouseClickEventHandle(e); });
    eventDispatcher.subscribe([this](MousePositionEvent e) { mousePositionEventHandle(e); });
    eventDispatcher.subscribe([this](KeyboardEvent e) { keyboardEventHandle(e); });

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<>dis(-50, 50.0f);

    m_world.initWorld();

    // temp
    /*for (int i = 0; i < 40096; i++) {
        auto x = dis(gen);
        auto y = dis(gen);
        auto z = dis(gen);
        cubePositions.push_back(glm::vec3(x, y, z));
    }*/
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
    m_world.update(dt);
    // m_camera.update(dt);
}

void PlayState::draw(const float dt)
{
    // rendering here..
    glClearColor(0.73f, 0.82f, 0.89f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_world.draw(dt);

    /*glm::mat4 view;
    view = m_camera.getViewMatrix();
    glm::mat4 projection;
    projection = glm::perspective(m_camera.m_zoom, 800.0f / 600.0f, 0.1f, 500.0f);

    m_frustum.CalculateFrustum(projection, view);

    std::vector<glm::mat4> models;
    std::vector<int> layers;

    int i = 0;
    for (auto pos : cubePositions) {
        if (m_frustum.CubeInFrustum(pos, glm::vec3(1, 1, 1))) {
            glm::mat4 model;
            model = glm::translate(model, pos);
            models.push_back(model);
            if (i % 2 == 0) {
                layers.push_back(0);
            } else {
                layers.push_back(3);
            }
        }
        i++;
    }

    m_model.bindPosition(models, layers);
    m_model.draw(view, projection);*/

    /*int i = 0;
    for (auto pos : cubePositions) {
        if (m_frustum.CubeInFrustum(pos, glm::vec3(1, 1, 1))) {
            glm::mat4 model;
            model = glm::translate(model, pos);
            if (i % 2 == 0) {
                m_model.draw(view, model, projection, 0);
            } else {
                m_model.draw(view, model, projection, 3);
            }
        }

        i++;
    }*/
}

PlayState::~PlayState()
{
    std::cout << "playstate deallocated\n";
    m_sigConnection.disconnect();
}
