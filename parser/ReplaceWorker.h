#ifndef LAB2_REPLACEWORKER_H
#define LAB2_REPLACEWORKER_H

#include "worker.h"

class ReplaceWorker: public Worker {
public:
    ReplaceWorker(const std::vector<std::string> &args);

    ~ReplaceWorker() = default;

    std::vector <std::string> & process(std::vector <std::string> & inp_text);

    std::string get_type() const;
};


#endif
