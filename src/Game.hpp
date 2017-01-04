#ifndef VOXELS_GAME_HPP
#define VOXELS_GAME_HPP


#include <memory>
#include "VoxelEngine.hpp"
#include "Window.hpp"

using namespace std;


class Game
{
private:
    std::unique_ptr<Window> window;
    std::unique_ptr<VoxelEngine> voxelEngine;

    const int windowWidth = 800;
    const int windowHeight = 600;
    const char *windowTitle = "LearnOpenGL";

public:
    Game();
    void gameLoop();
    ~Game();
};


#endif //VOXELS_GAME_HPP
