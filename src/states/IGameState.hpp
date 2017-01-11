#ifndef VOXELS_GAMESTATE_HPP
#define VOXELS_GAMESTATE_HPP

#include "../Game.hpp"

class Game;

class IGameState
{
protected:
    Game &m_game;

    virtual void mouseClickEventHandle(MouseClickEvent e) = 0;
    virtual void mousePositionEventHandle(MousePositionEvent e) = 0;
    virtual void keyboardEventHandle(KeyboardEvent e) = 0;
public:
    IGameState(Game &game): m_game(game) { }
    virtual void update(const float dt) = 0;
    virtual void draw(const float dt) = 0;
    virtual ~IGameState() = default;

};
#endif //VOXELS_GAMESTATE_HPP
