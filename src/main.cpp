#include "Game.hpp"
#include "states/PlayState.hpp"
#include <noise/noise.h>

using namespace std;
using namespace noise;

int main(int argc, char **argv) {
    module::Perlin myModule;
    double value = myModule.GetValue(1.25, 0.75, 0.5);
    printf("my fucking value %lf", value);

    exit(0);

    Game game;
    game.pushState(std::make_unique<PlayState>(game));
    game.gameLoop();
}