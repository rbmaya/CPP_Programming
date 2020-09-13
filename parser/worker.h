#ifndef LAB2_WORKER_H
#define LAB2_WORKER_H

#include "myException.h"
#include <fstream>
#include <string>
#include <vector>

class Worker{
public:
    explicit Worker(const std::vector <std::string> & args);

    virtual ~Worker() = default;

    virtual std::vector <std::string> & process(std::vector <std::string> & inp_text) = 0;

    virtual std::string get_type() const = 0;

protected:
    std::vector <std::string> args;
};



#endif
