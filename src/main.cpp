#include "Game.hpp"
#include "states/PlayState.hpp"

using namespace std;

int main(int argc, char **argv) {
    Game game;
    game.pushState(std::make_unique<PlayState>(game));
    game.gameLoop();
}