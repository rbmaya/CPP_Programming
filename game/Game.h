#ifndef LAB3_GAME_H
#define LAB3_GAME_H

#include <vector>
#include "Gamer.h"

class Gamer;

class Game{
public:
    void createGamer();

    void deleteGamers();

    void preparation();

    bool findWinner();

    void process();

    friend class Gamer;
private:
    Gamer *gam1;
    Gamer *gam2;
};


#endif
