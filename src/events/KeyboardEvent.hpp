#ifndef VOXELS_KEYBOARDEVENT_HPP
#define VOXELS_KEYBOARDEVENT_HPP

struct KeyboardEvent
{
    int m_key;
    int m_scancode;
    int m_action;
    int m_mods;

    KeyboardEvent(int key, int scancode, int action, int mods)
    : m_key(key)
    , m_scancode(scancode)
    , m_action(action)
    , m_mods(mods)
    { }
};

#endif //VOXELS_KEYBOARDEVENT_HPP
