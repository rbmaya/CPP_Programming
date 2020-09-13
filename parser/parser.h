#ifndef LAB2_PARSER_H
#define LAB2_PARSER_H

#include "worker.h"
#include "scheme.h"
#include "validator.h"
#include <map>
#include <fstream>

class Parser{
public:
    Parser(std::ifstream & inp_text_file);

    ~Parser();

    Scheme createScheme();

private:
    Validator* findSupport(const MetaInformation & inf);

    std::vector <std::string> parseLine(std::string & line);

    std::ifstream & inp_file;
    std::vector <Validator*> validators;
};

#endif
