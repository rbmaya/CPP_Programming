#ifndef LAB2_FACTORY_H
#define LAB2_FACTORY_H

#include <string>
#include "worker.h"
#include "validator.h"

class Factory {
public:
    Factory(const MetaInformation & inf);

    Worker* createWorker();
private:
    MetaInformation inf;
};


#endif
