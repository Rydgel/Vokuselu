#include "Game.hpp"
#include "states/PlayState.hpp"
#include <boost/signals2.hpp>
#include <iostream>
#include "events/KeyboardEvent.hpp"
#include "EventManager.hpp"

using namespace std;

int main() {
    auto hello = [] (KeyboardEvent e) { std::cout << "Hello, World!" << std::endl; };
    auto imad = [] (KeyboardEvent e) { std::cout << "Are you retarded sir" << std::endl; };

    EventManager eventManager;
    auto c = eventManager.subscribe(EventType::Keyboard, hello);
    auto c2 = eventManager.subscribe(EventType::Keyboard, imad);

    KeyboardEvent keyboardEvent(0, 0);
    eventManager.push(keyboardEvent);
    eventManager.push(keyboardEvent);
    eventManager.unsubscribe(c);
    eventManager.push(keyboardEvent);
}