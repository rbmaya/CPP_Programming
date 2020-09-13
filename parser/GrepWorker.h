#ifndef LAB2_GREPWORKER_H
#define LAB2_GREPWORKER_H

#include "worker.h"

class GrepWorker: public Worker {
public:
    GrepWorker(const std::vector<std::string> &args);

    ~GrepWorker() = default;

    std::vector <std::string> & process(std::vector <std::string> & inp_text_text);

    std::string get_type() const;
};


#endif
