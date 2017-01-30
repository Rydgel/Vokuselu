#include "World.hpp"

World::World(Game &game)
: m_game(game)
, m_camera(m_game.getEventDispatcherRef())
, m_model(m_game.getTextureArrayRef())
{

}

void World::initWorld()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<>dis(0, 131183);

    // for now just generate 1 chunk
    auto c1 = std::make_unique<Chunk>(dis(gen), 0, 0, 0);
    auto c2 = std::make_unique<Chunk>(dis(gen), Chunk::SIZE, 0, 0);
    auto c3 = std::make_unique<Chunk>(dis(gen), -Chunk::SIZE, 0, 0);
    auto c4 = std::make_unique<Chunk>(dis(gen), 0, 0, Chunk::SIZE);
    auto c5 = std::make_unique<Chunk>(dis(gen), 0, 0, -Chunk::SIZE);
    auto c6 = std::make_unique<Chunk>(dis(gen), Chunk::SIZE, 0, Chunk::SIZE);
    auto c7 = std::make_unique<Chunk>(dis(gen), -Chunk::SIZE, 0, -Chunk::SIZE);
    auto c8 = std::make_unique<Chunk>(dis(gen), Chunk::SIZE, 0, -Chunk::SIZE);
    auto c9 = std::make_unique<Chunk>(dis(gen), -Chunk::SIZE, 0, Chunk::SIZE);

    m_chunks.push_back(std::move(c1));
    m_chunks.push_back(std::move(c2));
    m_chunks.push_back(std::move(c3));
    m_chunks.push_back(std::move(c4));
    m_chunks.push_back(std::move(c5));
    m_chunks.push_back(std::move(c6));
    m_chunks.push_back(std::move(c7));
    m_chunks.push_back(std::move(c8));
    m_chunks.push_back(std::move(c9));
}

void World::generateCubesPositions()
{
    std::vector<glm::mat4> positions;
    std::vector<int> layers;

    for (auto &chunk : m_chunks) {
        auto chunkPositions = chunk->getCubesPositions();
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
