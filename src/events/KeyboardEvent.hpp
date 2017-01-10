#ifndef VOXELS_KEYBOARDEVENT_HPP
#define VOXELS_KEYBOARDEVENT_HPP

#include "IEvent.hpp"

struct KeyboardEvent : IEvent
{
    int m_key;
    int m_keystate;

    KeyboardEvent(int key, int keystate)
    : m_key(key)
    , m_keystate(keystate)
    {

    };

    virtual EventType getType() const
    {
        return EventType::Keyboard;
    }
};

#endif //VOXELS_KEYBOARDEVENT_HPP
