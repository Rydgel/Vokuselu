#ifndef VOXELS_PLAYSTATE_HPP
#define VOXELS_PLAYSTATE_HPP

#include "IGameState.hpp"
#include "../Model.hpp"
#include <iostream>

class PlayState : public IGameState
{
private:
    boost::signals2::connection m_sigConnection;
    Model m_model;

    virtual void mouseClickEventHandle(MouseClickEvent e);
    virtual void mousePositionEventHandle(MousePositionEvent e);
    virtual void keyboardEventHandle(KeyboardEvent e);
public:
    PlayState(Game &game);
    virtual void update(const float dt);
    virtual void draw(const float dt);
    virtual ~PlayState();
};


#endif //VOXELS_PLAYSTATE_HPP
