#include "DumpWorker.h"
#include <iostream>

DumpWorker::DumpWorker(const std::vector<std::string> &args) : Worker(args){}

std::vector <std::string> & DumpWorker::process(std::vector <std::string> & inp_text) {
    std::ofstream out(args[0]);

    try{
        if (!out.is_open()) throw OutFileNotOpen();
    }
    catch (const std::exception & exc){
        std::string error(exc.what());
        std::cerr << "Error! " << error << std::endl;
        throw EXIT_FAILURE;
    }

    for (auto it = inp_text.begin(); it != inp_text.end(); ++it){
        out << *it << "\n";
    }

    return inp_text;
}

std::string DumpWorker::get_type() const {
    return "dump";
}