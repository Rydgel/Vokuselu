#ifndef VOXELS_GAMESTATE_HPP
#define VOXELS_GAMESTATE_HPP

#include "../Game.hpp"

class Game;

class IGameState
{
protected:
    Game &m_game;
public:
    IGameState(Game &game): m_game(game) { }
    virtual void handleInput(const float dt) = 0;
    virtual void update(const float dt) = 0;
    virtual void draw(const float dt) = 0;
    virtual ~IGameState() = default;

};
#endif //VOXELS_GAMESTATE_HPP
