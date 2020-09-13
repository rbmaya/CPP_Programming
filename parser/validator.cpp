#include "validator.h"
#define ARGS_READ 1
#define ARGS_WRITE 1
#define ARGS_GREP 1
#define ARGS_SORT 0
#define ARGS_REPLACE 2
#define ARGS_DUMP 1


MetaInformation::MetaInformation(size_t id, const std::string & type, const std::vector <std::string> & args)
: id(id), type(type), args(args){}

size_t MetaInformation::get_id() const {
    return id;
}

std::string MetaInformation::get_type() const {
    return this->type;
}

size_t MetaInformation::get_count_args() const {
    return args.size();
}


std::vector <std::string>& MetaInformation::get_args() {
    return args;
}


bool ReadFileValidator::isSupport(MetaInformation inf) {
    return inf.get_type() == "readfile";
}

bool ReadFileValidator::validate(MetaInformation inf) {
    return inf.get_count_args() == ARGS_READ;
}

bool WriteFileValidator::isSupport(MetaInformation inf) {
    return inf.get_type() == "writefile";
}

bool WriteFileValidator::validate(MetaInformation inf) {
    return inf.get_count_args() == ARGS_WRITE;
}


bool GrepValidator::isSupport(MetaInformation inf) {
    return inf.get_type() == "grep";
}

bool GrepValidator::validate(MetaInformation inf) {
    return inf.get_count_args() == ARGS_GREP;
}


bool SortValidator::isSupport(MetaInformation inf) {
    return inf.get_type() == "sort";
}

bool SortValidator::validate(MetaInformation inf) {
    return inf.get_count_args() == ARGS_SORT;
}


bool ReplaceValidator::isSupport(MetaInformation inf) {
    return inf.get_type() == "replace";
}

bool ReplaceValidator::validate(MetaInformation inf) {
    return inf.get_count_args() == ARGS_REPLACE;
}

bool DumpValidator::isSupport(MetaInformation inf) {
    return inf.get_type() == "dump";
}

bool DumpValidator::validate(MetaInformation inf) {
    return inf.get_count_args() == ARGS_DUMP;
}


