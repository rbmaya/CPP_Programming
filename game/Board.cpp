#include <iostream>
#include "Board.h"

#define WHITE "\033[37m"
#define DEFAULT "\033[00m"
#define GREEN_LIGHT "\033[92m"
#define BLUE "\033[94m"

Ship::Ship(const std::pair<int, char> & coordinate, lengthShips length, Direction direction) :
        length(length), direction(direction), state(ALIVE) {
    this->coordinate.emplace_back(coordinate.first,(int)(coordinate.second) - 97);
}

bool Board::validateCoord(const Ship & ship) const {
    if ((ship.direction < HORIZONTALLY) || (ship.direction > VERTICALLY)) return false;
    if ((ship.coordinate[0].first < 0) || (ship.coordinate[0].first >  DEFAULT_WIDTH))
        return false;

    if ((ship.coordinate[0].second < 0) || (ship.coordinate[0].second >  DEFAULT_WIDTH))
        return false;

    for (int i = ship.length - 1; i >= 0; --i) {
        if (ship.direction == HORIZONTALLY) {
            int new_coordinate = ship.coordinate[0].second + i;
            if ((new_coordinate >= DEFAULT_WIDTH) || (new_coordinate < 0)) return false;

            for (int j = ship.coordinate[0].first - 1; j < 3 + ship.coordinate[0].first - 1; ++j) {
                for (int k = new_coordinate - 1; k < 3 + new_coordinate - 1; ++k) {
                    if ((j >= 0) && (k >= 0) && (j < DEFAULT_HEIGHT) && (k < DEFAULT_WIDTH)) {
                        if (board[j][k] == TRUE) return false;
                    }
                }
            }
        }
        if (ship.direction == VERTICALLY) {
            int new_coordinate = ship.coordinate[0].first + i;
            if ((new_coordinate >= DEFAULT_HEIGHT) || (new_coordinate < 0)) return false;

            for (int j = new_coordinate - 1; j < 3 + new_coordinate - 1; ++j) {
                for (int k = ship.coordinate[0].second - 1; k < 3 + ship.coordinate[0].second - 1; ++k) {
                    if ((j >= 0) && (k >= 0) && (j < DEFAULT_HEIGHT) && (k < DEFAULT_WIDTH)) {
                        if (board[j][k] == TRUE) return false;
                    }
                }
            }
        }
    }

    return true;
}

Board & Board::addShip(Ship &ship){
    for (int i = 0; i < ship.length; ++i) {
        if (ship.direction == HORIZONTALLY) {
            int new_coordinate = ship.coordinate[0].second + i;
            int old_coordinate = ship.coordinate[0].first;
            std::pair <int, int> new_pair(old_coordinate, new_coordinate);
            if (i) ship.coordinate.push_back(new_pair);
            board[ship.coordinate[0].first][new_coordinate] = TRUE;
        }
        if (ship.direction == VERTICALLY) {
            int new_coordinate = ship.coordinate[0].first + i;
            int old_coordinate = ship.coordinate[0].second;
            std::pair <int, int> new_pair(new_coordinate, old_coordinate);
            if (i) ship.coordinate.push_back(new_pair);
            board[new_coordinate][ship.coordinate[0].second] = TRUE;
        }
    }
    ships.push_back(ship);
    return *this;
}

Board::Board(){
    board = new Trit*[DEFAULT_HEIGHT];

    for (int i = 0; i < DEFAULT_HEIGHT; ++i) {
        board[i] = new Trit[DEFAULT_WIDTH];
        for (int j = 0; j < DEFAULT_WIDTH; ++j)
            board[i][j] = FALSE;
    }
}

void Board::initBoard() {
    for (int i = 0; i < DEFAULT_HEIGHT; ++i)
        for (int j = 0; j < DEFAULT_WIDTH; ++j)
            board[i][j] = UNKNOWN;
}

int Board::countDeadShips() const {
    return ships.size();
}


void Board::clearNear(const Ship &ship) {
    int cellI = ship.coordinate[0].first;
    int cellJ = ship.coordinate[0].second;

    if (ship.direction == HORIZONTALLY) {
        for (int j = cellJ - 1; j <= cellJ + ship.length; ++j) {
            if ((j >= 0) && (j < DEFAULT_HEIGHT)){
                if ((cellI - 1) >= 0)board[cellI - 1][j] = FALSE;
                if ((cellI + 1) < DEFAULT_HEIGHT)board[cellI + 1][j] = FALSE;
            }
        }
        if ((cellJ - 1) >= 0) board[cellI][cellJ - 1] = FALSE;
        if ((cellJ + ship.length) < DEFAULT_WIDTH) board[cellI][cellJ + ship.length] = FALSE;
    }

    if (ship.direction == VERTICALLY) {
        for (int i = cellI - 1; i <= cellI + ship.length; ++i) {
            if ((i >= 0) && (i < DEFAULT_HEIGHT)){
                if ((cellJ - 1) >= 0) board[i][cellJ - 1] = FALSE;
                if ((cellJ + 1 < DEFAULT_WIDTH)) board[i][cellJ + 1] = FALSE;
            }
        }
        if ((cellI - 1) >= 0) board[cellI - 1][cellJ] = FALSE;
        if ((cellI + ship.length) < DEFAULT_HEIGHT) board[cellI + ship.length][cellJ] = FALSE;
    }
}


void Board::show() {

    std::cout << "  ";
    for (int i = 0; i < DEFAULT_WIDTH; ++i)
        std::cout << WHITE << (unsigned char)(i + 97) << "  ";

    std::cout << std::endl;

    for (int i = 0; i < DEFAULT_HEIGHT; ++i) {
        std::cout << WHITE << i << DEFAULT;
        std::cout << WHITE << "┃" << DEFAULT;
        for (int j = 0; j < DEFAULT_WIDTH; ++j) {
            if (board[i][j] == TRUE) {
                std::cout << GREEN_LIGHT << "██"<< DEFAULT;
            } else if (board[i][j] == FALSE){
                std::cout << BLUE << "≋≋" << DEFAULT;
            }
            else{
                std::cout << WHITE << "▔▔" << DEFAULT;
            }
            std::cout << WHITE << "┃" << DEFAULT;
        }
        std::cout << std::endl;
    }
    std::cout << WHITE << "  ▔▔" << DEFAULT;
    for (int i = 0; i < DEFAULT_WIDTH - 1; ++i)
        std::cout << WHITE << " ▔▔" << DEFAULT;

    std::cout << std::endl;
    std::cout << std::endl;
}

void Ship::changeState(const std::pair<int, int> &coord) {
    for (int i = 0; i < (int)this->length; ++i) {
        if (this->coordinate[i] == coord) {
            if (i) {
                this->coordinate.erase(this->coordinate.begin() + i);
            }
            break;
        }
    }

    if (this->coordinate.size() == 1) this->state = DEAD;
    else this->state = INJURED;
}



Ship & Board::findInjuredShip(const std::pair<int, int> &coord) {
    for (auto & it : this->ships){
        for (int i = 0; i < it.length; ++i){
           if (it.coordinate[i] == coord) {
               return it;
           }
        }
    }

    return this->ships[0];
}

Ship Board::getCoordinate(std::pair<int, int> last_coord) {
    Ship & injuredShip = this->findInjuredShip(last_coord);
    return injuredShip;
}

State Board::Shot(const std::pair<int, int> &coord) {
    Ship & injuredShip = this->findInjuredShip(coord);
    injuredShip.changeState(coord);
    return injuredShip.state;
}

