#ifndef VOXELS_GAME_HPP
#define VOXELS_GAME_HPP

#include <memory>
#include <stack>
#include <sstream>
#include <cmath>
#include <boost/optional.hpp>
#include "VoxelEngine.hpp"
#include "Window.hpp"
#include "GameState.hpp"
#include "Timer.hpp"

using namespace std;

class GameState;

using WindowPtr = std::unique_ptr<Window>;
using VoxelEnginePtr = std::unique_ptr<VoxelEngine>;
using GameStatePtr = std::unique_ptr<GameState>;
using GameStateStack = std::stack<GameStatePtr>;

class Game
{
private:
    WindowPtr window;
    Timer timer;
    VoxelEnginePtr voxelEngine;
    GameStateStack states;

    const int windowWidth = 800;
    const int windowHeight = 600;
    const char *windowTitle = "LearnOpenGL";

public:
    Game();
    void pushState(GameStatePtr state);
    void popState();
    void changeState(GameStatePtr state);
    const boost::optional<GameStatePtr&> peekState();
    void gameLoop();
    ~Game();
};


#endif //VOXELS_GAME_HPP
