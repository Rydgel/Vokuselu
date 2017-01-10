#include "Game.hpp"
#include "states/PlayState.hpp"
#include <boost/signals2.hpp>
#include <iostream>
#include "events/KeyboardEvent.hpp"
#include "EventManager.hpp"

using namespace std;

int main() {
    auto hello = [] (IEvent e) {
        std::cout << "Hello, World!" << std::endl;
    };
    auto imad = [] (IEvent e) { std::cout << "Are you retarded sir" << std::endl; };

    EventManager eventManager;
    auto c = eventManager.subscribe(EventType::Keyboard, hello);
    auto c2 = eventManager.subscribe(EventType::Keyboard, imad);

    KeyboardEvent keyboardEvent(0, 0);
    eventManager.push(EventType::Keyboard, keyboardEvent);
    eventManager.push(EventType::Keyboard, keyboardEvent);
    eventManager.unsubscribe(c);
    eventManager.push(EventType::Keyboard, keyboardEvent);
}