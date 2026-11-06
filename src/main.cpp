#include "core/Game.h"
#include <cstdio>

int main(int, char**) {
    Game game;
    if (!game.init()) {
        std::fprintf(stderr, "Failed to initialise game.\n");
        return 1;
    }
    game.run();
    return 0;
}
