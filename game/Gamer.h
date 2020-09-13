#ifndef LAB3_Gamer_H
#define LAB3_Gamer_H

#include <string>
#include "Game.h"
#include "Board.h"

class Gamer {
public:
    Gamer() = default;
    virtual ~Gamer() = default;
    virtual void adjustOneTypeShip(const std::string & type, lengthShips length, int count) = 0;
    virtual void adjustShips() = 0;
    virtual void makeShot(Board & board1) = 0;

    friend class Game;
    friend class Board;
protected:
    std::string name;
    std::string type;
    Board *board;
    Board *opp_board;
};


class ConsoleGamer : public Gamer{
public:
    ConsoleGamer(const std::string & name, const std::string &type);
    ~ConsoleGamer();
    void adjustOneTypeShip(const std::string & type, lengthShips length, int count);
    void adjustShips();
    void makeShot(Board & board1);
};

class RandomGamer : public Gamer{
public:
    RandomGamer(const std::string & name, const std::string &type);
    ~RandomGamer();
    void adjustOneTypeShip(const std::string & type, lengthShips length, int count);
    void adjustShips();
    void makeShot(Board & board1);
};

class OptimalGamer: public Gamer{
public:
    OptimalGamer(const std::string & name, const std::string &type);
    ~OptimalGamer();
    void adjustOneTypeShip(const std::string & type, lengthShips length, int count);
    void adjustShips();
    void makeShot(Board & board1);
};


#endif
