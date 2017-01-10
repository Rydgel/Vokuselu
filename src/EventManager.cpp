#include "EventManager.hpp"

void EventManager::unsubscribe(SigConnection c)
{
    c.disconnect();
}

void EventManager::push(IEvent &eventData)
{
    m_sigmap[eventData.getType()](eventData);
}
