#include "Game.h"

#include <iostream>


int main() {
    int exitCode = EXIT_SUCCESS;
    Game game;
    try {
        exitCode = game.run();
    }
    catch (std::runtime_error& e) {
        std::cout << "Exception: " << e.what() << std::endl;
        game.exit();
    }

    return exitCode;
}