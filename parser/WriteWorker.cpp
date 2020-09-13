#include "WriteWorker.h"
#include "myException.h"
#include <iostream>

WriteWorker::WriteWorker(const std::vector<std::string> &args) : Worker(args) {}

std::vector <std::string> & WriteWorker::process(std::vector <std::string> & inp_text) {
    std::ofstream out(args[0]);

    try{
        if (!out.is_open()) throw OutFileNotOpen();
    }
    catch (const std::exception & exc){
        std::string error(exc.what());
        std::cerr << "Error! " << error << std::endl;
        throw EXIT_FAILURE;
    }

    for (auto & it : inp_text){
        out << it << "\n";
    }

    return inp_text;
}

std::string WriteWorker::get_type() const {
    return "writefile";
}