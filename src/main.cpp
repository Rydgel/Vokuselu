#include <iostream>
#include <unordered_map>

#include <boost/hana.hpp>
#include <boost/variant.hpp>
#include <boost/signals2.hpp>

namespace hana = boost::hana;

// My case wrapper
template <class Ret, class Caller>
struct CaseVisitor: boost::static_visitor<Ret> {
    CaseVisitor(const Caller & caller): caller_ { caller } {}

    template <class T>
    auto operator()(T & t) const { return caller_(t); }

    template <class T>
    auto operator()(const T & t) const { return caller_(t); }

    const Caller & caller_;
};

// Const variant version
template <class T, template <class...> class V, class F, class... Ts, class... Fs>
auto case_(const V<T, Ts...> & variant, F && f, Fs &&... fs) {
    auto caller = boost::hana::overload_linearly(f, fs...);

    using Caller  = decltype(caller);
    using Ret     = std::result_of_t<Caller(T)>;
    using Visitor = CaseVisitor<Ret, Caller>;

    const Visitor v { caller };

    return boost::apply_visitor(v, variant);
};

// Mutable variant version
template <class T, class... Ts, template <class...> class V, class F, class... Fs>
auto case_(V<T, Ts...> & variant, F && f, Fs &&... fs) {
    auto caller = boost::hana::overload_linearly(f, fs...);

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

// -----------------------------------------------------------------------------

// Event Types
struct MouseEvent    { };
struct KeyboardEvent { };

template <class ConcreteEvent>
using EventSignalT = boost::signals2::signal<void (ConcreteEvent)>;

constexpr auto eventSet = hana::tuple_t<
        MouseEvent,
        KeyboardEvent
>;
constexpr auto eventSignalSet = hana::transform(eventSet, hana::template_<EventSignalT>);

using Event       = decltype(make_variant_over(eventSet)      )::type;
using EventSignal = decltype(make_variant_over(eventSignalSet))::type;

// Dispatcher
struct EventDispatcher {
    using TypeHash = std::size_t;
    using SignalMap = std::unordered_map<TypeHash, EventSignal>;

    template <class ConcreteEvent>
    using EventSlot = std::function<void (ConcreteEvent)>;

    SignalMap m_signalMap;

    //
    // Subscribe
    //
    template <class ConcreteEvent>
    auto subscribeImpl(EventSlot<ConcreteEvent> handler) {
        using ConcreteSignal = EventSignalT<ConcreteEvent>;
        using Connection = boost::signals2::connection;

        static const auto eventHash = typeid(ConcreteEvent).hash_code();

        Connection conn;
        auto entry = m_signalMap.find(eventHash);

        if (entry != m_signalMap.end()) {
            // Signal already exists, update it with the new handler
            auto &signal = entry->second;

            conn = case_(signal,
                         [=](ConcreteSignal & sig) { return sig.connect(handler); },
                         [](auto &&) -> Connection {
                             throw std::runtime_error("I BROKE MY CONSTRAINT :'(");
                         }
            );
        }
        else {
            // Create and store a new signal
            ConcreteSignal s;
            conn = s.connect(handler);
            m_signalMap.emplace(eventHash, std::move(s));
        }

        return conn;
    }

    template <class Slot, class C, class R, class ConcreteEvent>
    auto subscribeDeduce(Slot slot, R (C::*)(ConcreteEvent) const) {
        // Only helps deducing the slot's first parameter type
        return subscribeImpl(EventSlot<ConcreteEvent> {slot});
    }

    template <class Slot>
    auto subscribe(Slot slot) {
        return subscribeDeduce(slot, &Slot::operator());
    }

    // todo add disconnect

    //
    // Push
    //
    template <class ConcreteEvent>
    auto pushImpl(const Event &event) {
        using ConcreteSignal = EventSignalT<ConcreteEvent>;

        static const auto eventHash = typeid(ConcreteEvent).hash_code();

        auto &concreteSignal = boost::get<ConcreteSignal>(m_signalMap[eventHash]);
        auto &concreteEvent = boost::get<ConcreteEvent>(event);

        concreteSignal(concreteEvent);
    }

    void push(const Event &event) {
        case_(event,
              [=](auto concreteEvent) {
                  this->pushImpl<decltype(concreteEvent)>(event);
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

    auto mouseTrigger    = [](MouseEvent m)    { std::cout << "Mouse\n";    };
    auto keyboardTrigger = [](KeyboardEvent k) { std::cout << "Keyboard\n"; };

    d.subscribe(mouseTrigger);
    d.subscribe(mouseTrigger);
    d.subscribe(mouseTrigger);
    d.subscribe(keyboardTrigger);
    d.subscribe(keyboardTrigger);
    auto c = d.subscribe(keyboardTrigger);
    c.disconnect();
    d.push(e);
}