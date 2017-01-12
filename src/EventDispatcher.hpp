#ifndef VOXELS_EVENTDISPATCHER_HPP
#define VOXELS_EVENTDISPATCHER_HPP

#include <iostream>
#include <unordered_map>

#include <boost/hana.hpp>
#include <boost/variant.hpp>
#include <boost/signals2.hpp>

#include "utils/Hana.hpp"
#include "events/MouseClickEvent.hpp"
#include "events/MousePositionEvent.hpp"
#include "events/KeyboardEvent.hpp"


// thx Globi for the help with meta programming

namespace hana = boost::hana;
namespace signals = boost::signals2;

// -----------------------------------------------------------------------------
template <class ConcreteEvent>
using EventSignal = signals::signal<void (ConcreteEvent)>;

// Add event types below, that's it !
constexpr auto event_set = hana::tuple_t<
        MouseClickEvent,
        KeyboardEvent,
        MousePositionEvent
>;

using Event = decltype(make_variant_over(event_set))::type;

// type_c<T> -> make_pair(type_c<T>, EventSignal<T>{})
auto event_signal_pair = [](auto type) {
    using T = typename decltype(type)::type;

    return hana::make_pair(type, EventSignal<T>{});
};

// Dispatcher
struct EventDispatcher {
    using SignalMap = decltype(
    hana::unpack(
            hana::transform(event_set, event_signal_pair),
            hana::make_map
    )
    );

    SignalMap signal_map;

    template <class Slot>
    auto subscribe(Slot slot) {
        using ConcreteEvent = typename FirstParameter<Slot>::type;

        auto & sig = signal_map[hana::type_c<ConcreteEvent>];

        return sig.connect(slot);
    }

    auto push(const Event & event) {
        case_(event,
              [&](auto concreteEvent) {
                  auto & signal = signal_map[hana::make_type(concreteEvent)];

                  return signal(concreteEvent);
              }
        );
    }
};

#endif //VOXELS_EVENTDISPATCHER_HPP
