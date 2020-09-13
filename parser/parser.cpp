#include <iostream>
#include "myException.h"
#include "validator.h"
#include "parser.h"


Parser::Parser(std::ifstream & inp_file): inp_file(inp_file) {
    auto *readFileValidator = new ReadFileValidator;
    validators.push_back(readFileValidator);

    auto *writeFileValidator = new WriteFileValidator;
    validators.push_back(writeFileValidator);

    auto *grepValidator = new GrepValidator;
    validators.push_back(grepValidator);

    auto *sortValidator = new SortValidator;
    validators.push_back(sortValidator);

    auto *replaceValidator = new ReplaceValidator;
    validators.push_back(replaceValidator);

    auto *dumpValidator = new DumpValidator;
    validators.push_back(dumpValidator);
}



Parser::~Parser() {
    for (auto & val : validators)
        delete val;
}


Validator* Parser::findSupport(const MetaInformation & inf) {
    for (auto & val : validators){
        if (val->isSupport(inf)) return val;
    }
    return nullptr;
}

Scheme Parser::createScheme(){
    std::string first_keyword;
    std::string buffer;

    getline(inp_file, first_keyword);

    Scheme scheme;

    if (first_keyword != "desc") {
        std::cout << "Wrong inp_textut Format!" << std::endl;
    } else {
        getline(inp_file, buffer);
        while ((buffer != "csed") && !(inp_file.eof())){
            std::vector <std::string> words = this->parseLine(buffer);

            std::string id = words[0], type_block = words[1];
            words.erase(words.begin(), words.begin() + 2);

            MetaInformation inf(stoi(id), type_block, words);

            try {
                Validator* fVal = findSupport(inf);
                if (!fVal) throw Unsupported();
                if (!fVal->validate(inf)) throw WrongArgs();
                scheme.add_Worker(inf);
            }

            catch (const std::exception & exc){
                std::string error(exc.what());
                std::cerr << "Error! " << error << std::endl;
                throw EXIT_FAILURE;
            }
            getline(inp_file, buffer);
        }
    }

    if (!inp_file.eof()) getline(inp_file, buffer);

    std::vector <std::string> numbers = this->parseLine(buffer);

    scheme.add_executers(numbers);

    return scheme;
}


std::vector <std::string> Parser::parseLine(std::string & line) {
    std::vector <std::string> words;
    std::string sub_buf;

    size_t length = line.length();

    size_t begin_pointer = 0, end_pointer = line.find(' ');
    while ((end_pointer < length) && (!line.empty())){
       sub_buf = line.substr(begin_pointer, end_pointer);
       if (!sub_buf.empty() && (sub_buf != "=") && (sub_buf != "->")) {
           words.push_back(sub_buf);
           sub_buf.clear();
       }
       line.erase(begin_pointer, end_pointer + 1);
       end_pointer = line.find(' ');
       if (end_pointer == std::string::npos) end_pointer = length - 1;
    }

    return words;
}


