#include "Game.h"


int main(int argc, char **argv) {
    Game *game = new Game;

    system("clear");

    game->createGamer();
    game->createGamer();

    game->preparation();

    game->process();

    game->deleteGamers();

    delete game;

    return 0;
}
