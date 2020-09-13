#include <iostream>
#include <cstdlib>
#include <limits>
#include "Game.h"

#define COUNT_SHIPS 10

static void wait(){
    std::cout<<"Press any key to continue." << std::endl;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.clear();
    std::cin.get();
}

void Game::createGamer() {
    static std::string number = "first";
    while(true) {
        std::cout << "Enter the type of " << number << " Gamer: user / random / optimal" << std::endl;
        std::string type;
        std::cin >> type;

        std::cout << "Enter the name of " << number << " Gamer: " << std::endl;
        std::string name;
        std::cin >> name;

        if (type == "user") {
            if (number == "first") gam1 = new ConsoleGamer(name, "console");
            else gam2 = new ConsoleGamer(name, "console");
            system("clear");
            break;
        } else if (type == "random"){
            if (number == "first") gam1 = new RandomGamer(name, "random");
            else gam2 = new RandomGamer(name, "random");
            system("clear");
            break;
        } else if (type == "optimal") {
            if (number == "first") gam1 = new OptimalGamer(name, "optimal");
            else gam2 = new OptimalGamer(name, "optimal");
            system("clear");
            break;
        }
        else {
            std::cout << "Please, try again!" << std::endl;
            wait();
            std::cin.ignore(std::cin.rdbuf()->in_avail());
        }

        system("clear");
    }

    number = "second";
}


void Game::deleteGamers() {
    delete gam1;
    delete gam2;
}


void Game::preparation() {
    gam1->opp_board->initBoard();

    std::cout << "Ship's adjustment for the " << gam1->name << "." << std::endl;
    wait();
    system("clear");

    if ((gam1->type == "random") || (gam1->type == "optimal"))
        std::cout << "Please, wait. Board is generating..." << std::endl;
    gam1->adjustShips();
    system("clear");

    gam2->opp_board->initBoard();
    std::cout << "Ship's adjustment for the " << gam2->name << "." << std::endl;
    wait();
    system("clear");
    if ((gam2->type == "random") || (gam2->type == "optimal"))
        std::cout << "Please, wait. Board is generating..." << std::endl;
    gam2->adjustShips();
    system("clear");

    std::cout << "Your boards now:" << std::endl;

    std::cout << "Board of " << gam1->name << ":" << std::endl;

    gam1->board->show();

    std::cout << "Board of " << gam2->name << ":" << std::endl;

    gam2->board->show();
}


bool Game::findWinner() {
    if (gam1->opp_board->countDeadShips() == COUNT_SHIPS) {
        std::cout  << gam1->name << " is winner!" << std::endl;
        return true;
    }
    if (gam2->opp_board->countDeadShips() == COUNT_SHIPS) {
        std::cout << gam1->name << " is winner!" << std::endl;
        return true;
    }
    return false;
}


void Game::process() {
    system("clear");
    while(true){
        gam1->makeShot(*(gam2->board));
        wait();
        system("clear");

        if (findWinner()) break;

        gam2->makeShot(*(gam1->board));
        wait();
        system("clear");

        if (findWinner()) break;
    }
}
