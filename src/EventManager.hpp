#ifndef VOXELS_EVENTMANAGER_HPP
#define VOXELS_EVENTMANAGER_HPP

#include <boost/signals2.hpp>
#include <boost/variant.hpp>
#include <iostream>
#include "events/IEvent.hpp"
#include "events/KeyboardEvent.hpp"
#include "events/EventTypes.hpp"


using Signal = boost::signals2::signal<void (IEvent)>;
using SignalMap = std::map<EventType, Signal>;
using SigConnection = boost::signals2::connection;

class EventManager
{
private:
    SignalMap m_sigmap;
public:
    template <class F>
    SigConnection subscribe(EventType t, F f)
    {
        if (m_sigmap.find(t) == m_sigmap.end()) {
            m_sigmap[t] = Signal();
        }

        return m_sigmap[t].connect(f);
    }

    void unsubscribe(SigConnection c);
    void push(EventType et, IEvent eventData);
};

#endif //VOXELS_EVENTMANAGER_HPP
