#include "EventDispatcher.hpp"

EventDispatcher::EventChannel &EventDispatcher::subscribe(EventType filter)
{
    // Register a new channel
    auto event_channel_ptr = std::make_unique<EventChannel>();
    auto &event_channel = *event_channel_ptr;
    event_channels[filter].emplace_back(std::move(event_channel_ptr));
    // Return a reference to it
    return event_channel;
}

void EventDispatcher::push(EventType filter, Event event)
{
    for (auto &channel: event_channels[filter])
        channel->push(event);
}
