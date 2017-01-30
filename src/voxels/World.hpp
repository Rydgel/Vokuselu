#ifndef VOXELS_WORLD_HPP
#define VOXELS_WORLD_HPP

#include <vector>
#include <random>
#include "Chunk.hpp"
#include "../opengl/Frustum.hpp"
#include "../Game.hpp"
#include "../opengl/Camera.hpp"
#include "../opengl/CubeModel.hpp"

class World
{
private:
    Game &m_game;
    std::vector<std::unique_ptr<Chunk>> m_chunks;
    Camera m_camera;
    Frustum m_frustum;
    CubeModel m_model;
public:
    World(Game &game);
    void initWorld();
    void generateCubesPositions();
    void draw(const float dt);
    void update(const float dt);
    ~World();
};


#endif //VOXELS_WORLD_HPP
