#include "Gamer.h"
#include "Board.h"
#include <iostream>
#include <limits>
#include <ctime>


static void wait(){
    std::cout << "Press any key to continue." << std::endl;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.clear();
    std::cin.get();
}


ConsoleGamer::ConsoleGamer(const std::string & name, const std::string & type) {
    this->name = name;
    this->type = type;
    board = new Board();
    opp_board = new Board();
}


ConsoleGamer::~ConsoleGamer() {
    delete board;
    delete opp_board;
}


RandomGamer::RandomGamer(const std::string & name, const std::string & type) {
    this->name = name;
    this->type = type;
    board = new Board();
    opp_board = new Board();
}


RandomGamer::~RandomGamer() {
    delete board;
    delete opp_board;
}


OptimalGamer::OptimalGamer(const std::string & name, const std::string & type){
    this->name = name;
    this->type = type;
    board = new Board();
    opp_board = new Board();
}


OptimalGamer::~OptimalGamer(){
    delete board;
    delete opp_board;
}


void ConsoleGamer::adjustOneTypeShip(const std::string & type, lengthShips length, int count) {
    for (int i = 0; i < count; ++i) {
        while (true) {
            this->board->show();
            std::cout << "Enter coordinates " << type << ":" << std::endl;
            std::pair<int, char> coordinate;
            std::cin >> coordinate.second >> coordinate.first;
            if (type != "torpedo(1)") std::cout << "Enter direction (1 - horizontally, 2 - vertically):" << std::endl;
            int direction = HORIZONTALLY;
            if (type != "torpedo(1)") std::cin >> direction;

            Ship ship(coordinate, length, static_cast<Direction>(direction));

            if (this->board->validateCoord(ship)){
                this->board->addShip(ship);
                system("clear");
                break;
            } else {
                std::cout << "Wrong coordinates! Please, try again." << std::endl;
                wait();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.clear();
                system("clear");
            }
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.clear();
        system("clear");
    }
}


void RandomGamer::adjustOneTypeShip(const std::string & type, lengthShips length, int count) {
    for (int i = 0; i < count; ++i) {
        while (true) {
            srand(time(NULL));
            std::pair<int, int> coordinate;
            coordinate.first = rand() % (DEFAULT_HEIGHT);
            coordinate.second = 97 + rand() % (DEFAULT_WIDTH);
            int direction = 1 + rand() % 2;

            Ship ship(coordinate, length, static_cast<Direction>(direction));

            if (this->board->validateCoord(ship)){
                this->board->addShip(ship);
                break;
            }
        }
    }
}


void OptimalGamer::adjustOneTypeShip(const std::string & type, lengthShips length, int count) {
    for (int i = 0; i < count; ++i) {
        while (true) {
            srand(time(NULL));
            std::pair<int, int> coordinate;
            coordinate.first = rand() % (DEFAULT_HEIGHT);
            coordinate.second = 97 + rand() % (DEFAULT_WIDTH);
            int direction = 1 + rand() % 2;

            Ship ship(coordinate, length, static_cast<Direction>(direction));

            if (this->board->validateCoord(ship)){
                this->board->addShip(ship);
                break;
            }
        }
    }
}


void ConsoleGamer::adjustShips() {
    this->adjustOneTypeShip("battleship(4)", LEN_BATTLESHIP, 1);

    this->adjustOneTypeShip("cruiser(3)", LEN_CRUISER, 2);

    this->adjustOneTypeShip("destroyer(2)", LEN_DESTROYER, 3);

    this->adjustOneTypeShip("torpedo(1)", LEN_TORPEDO, 4);

    std::cout << "Board of " << this->name << ":" << std::endl;

    this->board->show();

    wait();
}


void RandomGamer::adjustShips() {
    this->adjustOneTypeShip("battleship(4)", LEN_BATTLESHIP, 1);

    this->adjustOneTypeShip("cruiser(3)", LEN_CRUISER, 2);

    this->adjustOneTypeShip("destroyer(2)", LEN_DESTROYER, 3);

    this->adjustOneTypeShip("torpedo(1)", LEN_TORPEDO, 4);

    std::cout << "Board of " << this->name << ":" << std::endl;

    this->board->show();

    wait();
}


void OptimalGamer::adjustShips() {
    this->adjustOneTypeShip("battleship(4)", LEN_BATTLESHIP, 1);

    this->adjustOneTypeShip("cruiser(3)", LEN_CRUISER, 2);

    this->adjustOneTypeShip("destroyer(2)", LEN_DESTROYER, 3);

    this->adjustOneTypeShip("torpedo(1)", LEN_TORPEDO, 4);

    std::cout << "Board of " << this->name << ":" << std::endl;

    this->board->show();

    wait();
}


void RandomGamer::makeShot(Board &board1) {
    std::pair<int, char> coord;

    while (true) {
        std::cout << this->name << "'s turn." << std::endl;
        coord.first = rand() % (DEFAULT_HEIGHT);
        coord.second = 97 + rand() % (DEFAULT_WIDTH);

        std::cout << "Generated coordinate: " << coord.second << " " << coord.first << std::endl;

        coord.second -= 97;

        if (this->opp_board->board[coord.first][coord.second] == UNKNOWN){
            break;
        } else {
            system("clear");
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.clear();
        }
    }

    State state = ALIVE;
    if (board1.board[coord.first][coord.second] == TRUE)
        state = board1.Shot(coord);

    if (state == INJURED) this->opp_board->board[coord.first][coord.second] = TRUE;
    if (state == ALIVE) this->opp_board->board[coord.first][coord.second] = FALSE;
    if (state == DEAD) {
        Ship ship(std::make_pair(0, 'a'), LEN_TORPEDO, VERTICALLY);
        this->opp_board->board[coord.first][coord.second] = TRUE;
        ship = board1.getCoordinate(coord);
        this->opp_board->addShip(ship);
        this->opp_board->clearNear(ship);
    }

    this->opp_board->show();
}


void OptimalGamer::makeShot(Board &board1) {
    std::pair<int, char> coord;

    while (true) {
        std::cout << this->name << "'s turn." << std::endl;
        coord.first = rand() % (DEFAULT_HEIGHT);
        coord.second = 97 + rand() % (DEFAULT_WIDTH);

        std::cout << "Generated coordinate: " << coord.second << " " << coord.first << std::endl;

        coord.second -= 97;

        if (this->opp_board->board[coord.first][coord.second] == UNKNOWN){
            break;
        } else {
            system("clear");
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.clear();
        }
    }

    Ship ship(std::make_pair(coord.first, coord.second + 97), LEN_TORPEDO, VERTICALLY);

    State state = ALIVE;
    if (board1.board[coord.first][coord.second] == TRUE)
        state = board1.Shot(coord);

    if (state == INJURED) this->opp_board->board[coord.first][coord.second] = TRUE;
    if (state == ALIVE) this->opp_board->board[coord.first][coord.second] = FALSE;
    if (state == DEAD) {
        this->opp_board->board[coord.first][coord.second] = TRUE;
        ship = board1.getCoordinate(coord);
        this->opp_board->addShip(ship);
        this->opp_board->clearNear(ship);
    }

    this->opp_board->show();
}


void ConsoleGamer::makeShot(Board &board1) {
    std::pair<int, char> coord;

    while(true) {
       std::cout << this->name << "'s turn." << std::endl;
       this->opp_board->show();

       std::cout << "Enter coordinates of shot:" << std::endl;

       std::cin >> coord.second >> coord.first;

       coord.second -= 97;

       if ((coord.first >= 0) && (coord.first < DEFAULT_HEIGHT) && (coord.second >= 0) && (coord.second < DEFAULT_WIDTH)){
           system("clear");
           break;
       } else {
           std::cout << "Wrong coordinates! Please, try again." << std::endl;
           wait();
           std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
           std::cin.clear();
           system("clear");
       }
    }


    if (this->opp_board->board[coord.first][(int)coord.second] != UNKNOWN) return;

    Ship ship(std::make_pair(coord.first, coord.second + 97), LEN_TORPEDO, VERTICALLY);

    State state = ALIVE;
    if (board1.board[coord.first][coord.second] == TRUE)
        state = board1.Shot(coord);

    if (state == INJURED) this->opp_board->board[coord.first][coord.second] = TRUE;
    if (state == ALIVE) this->opp_board->board[coord.first][coord.second] = FALSE;
    if (state == DEAD) {
        this->opp_board->board[coord.first][coord.second] = TRUE;
        ship = board1.getCoordinate(coord);
        this->opp_board->addShip(ship);
        this->opp_board->clearNear(ship);
    }

    std::cout << this->name << "'s turn." << std::endl;
    this->opp_board->show();
}

