#ifndef VOXELS_EVENTDISPATCHER_HPP
#define VOXELS_EVENTDISPATCHER_HPP

#include <chrono>
#include <random>
#include <iostream>
#include <memory>
#include <array>
#include <boost/fiber/all.hpp>
#include "Event.hpp"
#include "EventType.h"

namespace chrono = std::chrono;
namespace fibers = boost::fibers;
namespace this_fiber = boost::this_fiber;
using namespace std::literals::chrono_literals;

class EventDispatcher
{
    using EventChannel = fibers::unbuffered_channel<Event>;
    using EventChannels = std::vector<std::unique_ptr<EventChannel>>;
private:
    std::array<EventChannels, EVENT_TYPE_COUNT> event_channels;
public:
    EventChannel &subscribe(EventType filter);
    void push(EventType filter, Event event);
};


#endif //VOXELS_EVENTDISPATCHER_HPP
