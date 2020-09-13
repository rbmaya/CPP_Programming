#ifndef LAB2_DUMPWORKER_H
#define LAB2_DUMPWORKER_H

#include "worker.h"

class DumpWorker: public Worker {
public:
    DumpWorker(const std::vector<std::string> &args);

    ~DumpWorker() = default;

    std::vector <std::string> & process(std::vector <std::string> & inp_text_text);

    std::string get_type() const;
};



#endif
