#include "ReaderWorker.h"
#include <iostream>
#include "myException.h"

ReaderWorker::ReaderWorker(const std::vector<std::string> &args) : Worker(args) {}


std::vector <std::string> & ReaderWorker::process(std::vector <std::string> & inp_text) {
    std::ifstream inp(args[0]);
    try{
        if (!(inp.is_open())) throw InpFileNotOpen();
    }


    catch (const std::exception & exc){
            std::string error(exc.what());
            std::cerr << "Error! " << error << std::endl;
            throw EXIT_FAILURE;
    }

    std::string buffer;

    while (!inp.eof()){
        getline(inp, buffer);
        inp_text.push_back(buffer);
    }

    return inp_text;
}

std::string ReaderWorker::get_type() const {
    return "readfile";
}