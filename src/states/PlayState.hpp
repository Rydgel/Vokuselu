#ifndef VOXELS_PLAYSTATE_HPP
#define VOXELS_PLAYSTATE_HPP

#include "IGameState.hpp"
#include <iostream>

class PlayState : public IGameState
{
public:
    PlayState(Game &game): IGameState(game) { };
    virtual void handleInput(const float dt);
    virtual void update(const float dt);
    virtual void draw(const float dt);
    virtual ~PlayState() {
        std::cout << "playstate deallocated\n";
    }
};


#endif //VOXELS_PLAYSTATE_HPP
