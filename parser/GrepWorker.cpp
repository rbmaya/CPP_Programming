#include "GrepWorker.h"

GrepWorker::GrepWorker(const std::vector<std::string> &args) : Worker(args){}

std::vector <std::string> & GrepWorker::process(std::vector <std::string> &inp_text) {
    std::string keyword = args[0];

    for (auto it = inp_text.begin() ; it != inp_text.end(); ++it){
        size_t pos = it->find(keyword);
        if (pos == std::string::npos) {
            inp_text.erase(it);
            --it;
        }
    }

    return inp_text;
}

std::string GrepWorker::get_type() const {
    return "grep";
}