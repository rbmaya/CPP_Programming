#ifndef LAB3_BOARD_H
#define LAB3_BOARD_H

#include <vector>

#define DEFAULT_WIDTH 10
#define DEFAULT_HEIGHT 10

enum State{
    ALIVE,
    INJURED,
    DEAD
};


enum Trit{
    FALSE,
    UNKNOWN,
    TRUE
};


enum lengthShips{
    LEN_TORPEDO = 1,
    LEN_DESTROYER,
    LEN_CRUISER,
    LEN_BATTLESHIP
};


enum Direction{
    HORIZONTALLY = 1,
    VERTICALLY
};


class Ship{
public:
    Ship(const std::pair<int, char> &coordinate, lengthShips length, Direction direction);

    void changeState(const std::pair<int, int> &coord);

    friend class Board;
    friend class RandomGamer;
    friend class ConsoleGamer;
    friend class OptimalGamer;
private:
    std::vector <std::pair <int, int>> coordinate;
    lengthShips length;
    Direction direction;
    State state;
};


class Board{
public:
    Board();

    int countDeadShips() const;

    void initBoard();

    void clearNear(const Ship & ship);

    bool validateCoord(const Ship & ship) const;

    Board & addShip(Ship & ship);

    void show();

    Ship getCoordinate(std::pair <int, int> last_coord);

    State Shot(const std::pair <int, int> & coord);

    Ship & findInjuredShip(const std::pair <int, int> & coord);

    friend class ConsoleGamer;
    friend class RandomGamer;
    friend class OptimalGamer;
private:
    Trit **board;
    std::vector <Ship> ships;
};


#endif
