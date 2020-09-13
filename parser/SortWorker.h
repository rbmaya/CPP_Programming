#ifndef LAB2_SORTWORKER_H
#define LAB2_SORTWORKER_H

#include "worker.h"

class SortWorker: public Worker {
public:
    SortWorker(const std::vector<std::string> &args);

    std::vector <std::string> & process(std::vector <std::string> & inp_text);

    std::string get_type() const;
};


#endif
