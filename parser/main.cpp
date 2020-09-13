#include <string>
#include <iostream>
#include "myException.h"
#include "parser.h"

int main(int argv, char **argc) {

    std::ifstream inp(argc[1]);

    try{
        if (!inp.is_open()) throw InpFileNotOpen();
    }
    catch (const std::exception & exc){
        std::string error(exc.what());
        std::cerr << "Error! " << error << std::endl;
        return EXIT_FAILURE;
    }

    Parser parser(inp);

    auto *scheme = new Scheme;

    try{
        *scheme  = parser.createScheme();
    }

    catch (int exc){
        return EXIT_FAILURE;
    }

    try{
        scheme->process();
    }

    catch (int exc){
        return EXIT_FAILURE;
    }

    delete scheme;

    return EXIT_SUCCESS;
}