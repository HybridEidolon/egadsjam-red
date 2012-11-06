#include <iostream>

#include <vector>

#include <SDL_main.h>

#include "Game.h"

using namespace std;

int main(int argc, char* argv[]) {
    cout << "Hello, world!" << endl;
    Game game = Game();

    game.init();
    game.run();

    return 0;
}
