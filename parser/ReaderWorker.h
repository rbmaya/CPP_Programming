#ifndef LAB2_READERWORKER_H
#define LAB2_READERWORKER_H

#include "worker.h"

class ReaderWorker: public Worker{
public:
    ReaderWorker(const std::vector<std::string> &args);

    ~ReaderWorker() = default;

    std::vector <std::string> & process(std::vector <std::string> & inp_text);

    std::string get_type() const;
};

#endif