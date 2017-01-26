#ifndef VOXELS_GAME_HPP
#define VOXELS_GAME_HPP

#include <memory>
#include <stack>
#include <sstream>
#include <cmath>
#include <boost/optional.hpp>
#include "EventDispatcher.hpp"
#include "Window.hpp"
#include "states/IGameState.hpp"
#include "Timer.hpp"
#include "opengl/TextureArray.hpp"

using namespace std;

class IGameState;

using WindowPtr = std::unique_ptr<Window>;
using GameStatePtr = std::unique_ptr<IGameState>;
using GameStateStack = std::stack<GameStatePtr>;

class Game
{
private:
    EventDispatcher m_eventDispatcher;
    WindowPtr m_window;
    Timer m_timer;
    GameStateStack m_states;
    TextureArray m_textureArray;

    const int m_windowWidth = 800;
    const int m_windowHeight = 600;
    const char *m_windowTitle = "LearnOpenGL";

public:
    Game();
    void pushState(GameStatePtr state);
    void popState();
    void changeState(GameStatePtr state);
    const boost::optional<GameStatePtr&> peekState();
    WindowPtr &getWindowRef();
    EventDispatcher &getEventDispatcherRef();
    TextureArray &getTextureArrayRef();
    void gameLoop();
    ~Game();
};


#endif //VOXELS_GAME_HPP
