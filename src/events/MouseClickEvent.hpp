#ifndef VOXELS_MOUSEEVENT_HPP
#define VOXELS_MOUSEEVENT_HPP

struct MouseClickEvent
{
    int m_button;
    int m_action;
    int m_mods;

    MouseClickEvent(int button, int action, int mods)
    : m_button(button)
    , m_action(action)
    , m_mods(mods)
    {

    }
};

#endif //VOXELS_MOUSEEVENT_HPP
