#include "SortWorker.h"
#include <algorithm>

SortWorker::SortWorker(const std::vector<std::string> &args) : Worker(args) {}

std::vector <std::string> & SortWorker::process(std::vector <std::string> & inp_text) {

    std::sort(inp_text.begin(), inp_text.end());

    return inp_text;
}

std::string SortWorker::get_type() const {
    return "sort";
}
