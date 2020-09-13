#ifndef LAB2_WRITEWORKER_H
#define LAB2_WRITEWORKER_H

#include "worker.h"


class WriteWorker : public Worker{
public:
    WriteWorker(const std::vector<std::string> &args);

    ~WriteWorker() = default;

    std::vector <std::string> & process(std::vector <std::string> & inp_text);

    std::string get_type() const;
};


#endif