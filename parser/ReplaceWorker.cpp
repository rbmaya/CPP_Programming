#include "ReplaceWorker.h"

ReplaceWorker::ReplaceWorker(const std::vector<std::string> &args) : Worker(args) {};

std::vector <std::string> & ReplaceWorker::process(std::vector <std::string> & inp_text){
    std::string old_word = args[0];
    std::string new_word = args[1];
    size_t old_len = old_word.length();

    for (auto & it : inp_text){
        size_t pos = it.find(old_word);
        while (pos != std::string::npos) {
            it.replace(it.begin() + pos, it.begin() + pos + old_len, new_word);
            pos = it.find(old_word);
        }
    }

    return inp_text;
};

std::string ReplaceWorker::get_type() const {
    return "replace";
}