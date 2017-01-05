#ifndef VOXELS_GAMESTATE_HPP
#define VOXELS_GAMESTATE_HPP

#include "Game.hpp"

class Game;

class GameState
{
public:
    Game &game_;

    GameState(Game &game): game_(game) { }
    virtual void draw(const float dt) = 0;
    virtual void update(const float dt) = 0;
    virtual void handleInput(const float dt) = 0;
    virtual ~GameState() = default;

};
#endif //VOXELS_GAMESTATE_HPP
