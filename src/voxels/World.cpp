#include "World.hpp"

World::World(Game &game)
: m_game(game)
, m_camera(m_game.getEventDispatcherRef())
, m_model(m_game.getTextureArrayRef())
{

}

void World::initWorld()
{
    // for now just generate 1 chunk
    Chunk c1;
    c1.initChunk(0, 0, 0);
    Chunk c2;
    c2.initChunk(16, 0, 0);
    Chunk c3;
    c3.initChunk(-16, 0, 0);
    Chunk c4;
    c4.initChunk(0, 0, 16);
    Chunk c5;
    c5.initChunk(0, 0, -16);

    Chunk c6;
    c6.initChunk(16, 0, 16);

    Chunk c7;
    c7.initChunk(-16, 0, -16);

    Chunk c8;
    c8.initChunk(16, 0, -16);

    Chunk c9;
    c9.initChunk(-16, 0, 16);

    m_chunks.push_back(c1);
    m_chunks.push_back(c2);
    m_chunks.push_back(c3);
    m_chunks.push_back(c4);
    m_chunks.push_back(c5);
    m_chunks.push_back(c6);
    m_chunks.push_back(c7);
    m_chunks.push_back(c8);
    m_chunks.push_back(c9);
}

void World::generateCubesPositions()
{
    std::vector<glm::mat4> positions;
    std::vector<int> layers;

    for (auto &chunk : m_chunks) {
        auto chunkPositions = chunk.getCubesPositions();
        for (auto &posLayer : chunkPositions) {
            auto pos = glm::vec3(posLayer.x, posLayer.y, posLayer.z);
            auto layer = (int) posLayer.w;
            if (m_frustum.CubeInFrustum(pos, glm::vec3(1, 1, 1))) {
                glm::mat4 model;
                model = glm::translate(model, pos);
                positions.push_back(model);
                layers.push_back(layer);
            }
        }
    }

    m_model.bindPosition(positions, layers);
}

void World::draw(const float dt)
{
    glm::mat4 view;
    view = m_camera.getViewMatrix();
    glm::mat4 projection;
    projection = glm::perspective(m_camera.m_zoom, 800.0f / 600.0f, 0.1f, 500.0f);

    m_frustum.CalculateFrustum(projection, view);
    generateCubesPositions();
    m_model.draw(view, projection);
}

void World::update(const float dt)
{
    m_camera.update(dt);
}

World::~World()
{

}
