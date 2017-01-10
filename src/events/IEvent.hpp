#ifndef VOXELS_IEVENT_HPP
#define VOXELS_IEVENT_HPP

#include "EventTypes.hpp"

struct IEvent
{
    virtual EventType getType() const = 0;
};

#endif //VOXELS_IEVENT_HPP
