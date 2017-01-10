#include "EventManager.hpp"

void EventManager::unsubscribe(SigConnection c)
{
    c.disconnect();
}

void EventManager::push(EventType et, IEvent eventData)
{
    m_sigmap[et](eventData);
}
