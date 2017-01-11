#include <iostream>
#include <unordered_map>

#include <boost/hana.hpp>
#include <boost/variant.hpp>
#include <boost/signals2.hpp>

namespace hana = boost::hana;
namespace signals = boost::signals2;

// My case wrapper
template <class Ret, class Caller>
struct CaseVisitor: boost::static_visitor<Ret> {
    CaseVisitor(const Caller & caller): caller_ { caller } {}

    template <class T>
    auto operator()(const T & t) const { return caller_(t); }

    const Caller & caller_;
};

// Const variant version
template <class T, template <class...> class V, class F, class... Ts, class... Fs>
auto case_(const V<T, Ts...> & variant, F && f, Fs &&... fs) {
    auto caller = hana::overload_linearly(f, fs...);

    using Caller  = decltype(caller);
    using Ret     = std::result_of_t<Caller(T)>;
    using Visitor = CaseVisitor<Ret, Caller>;

    const Visitor v { caller };

    return boost::apply_visitor(v, variant);
};

// Hana -> boost::variant helper
auto make_variant_over = hana::reverse_partial(
        hana::unpack,
        hana::template_<boost::variant>
);

// Argument type deduction helper
template <class F>
struct FirstParameter {
    template <class R, class C, class P1>
    static constexpr auto deduce(R (C::*)(P1) const) {
        return hana::decltype_(hana::type_c<P1>); // Strips const-ref qualifiers
    }

    using type = typename decltype(deduce(&F::operator()))::type;
};

// -----------------------------------------------------------------------------

// Event Types
struct MouseEvent    { };
struct KeyboardEvent { };

template <class ConcreteEvent>
using EventSignal = signals::signal<void (ConcreteEvent)>;

// Add event types below, that's it !
constexpr auto event_set = hana::tuple_t<
        MouseEvent,
        KeyboardEvent
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

int main(int argc, char **argv) {
    Event e;

    if (argc > 1)
        e = MouseEvent{};
    else
        e = KeyboardEvent{};

    EventDispatcher d;

    auto mouse_trigger    = [](MouseEvent m)    { std::cout << "Mouse\n";    };
    auto keyboard_trigger = [](KeyboardEvent k) { std::cout << "Keyboard\n"; };

    auto c1 = d.subscribe(mouse_trigger);
    auto c2 = d.subscribe(mouse_trigger);
    auto c3 = d.subscribe(keyboard_trigger);
    auto c4 = d.subscribe(keyboard_trigger);

    d.push(e);

    c1.disconnect();
    c3.disconnect();

    d.push(e);
}