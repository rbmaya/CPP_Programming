#ifndef LAB2_SCHEME_H
#define LAB2_SCHEME_H

#include <map>
#include <vector>
#include "worker.h"
#include "validator.h"

class Scheme{
public:
    void add_Worker(const MetaInformation & inf);

    void add_executers(const std::vector <std::string> & numbers);

    void process();

private:
    std::map <int, Worker*> workers;
    std::vector <int> executers;
};



#endif