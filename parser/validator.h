#ifndef LAB2_VALIDATOR_H
#define LAB2_VALIDATOR_H

#include "worker.h"


class MetaInformation{
public:
    MetaInformation(size_t id, const std::string & type, const std::vector <std::string> & args);

    size_t get_id() const;

    std::string get_type() const;

    size_t get_count_args() const;

    std::vector <std::string> & get_args();

private:
    size_t id;
    std::string type;
    std::vector <std::string> args;
};


class Validator{
public:
    virtual ~Validator() = default;

    virtual bool isSupport(MetaInformation inf) = 0;

    virtual bool validate(MetaInformation inf) = 0;
};



class ReadFileValidator: public Validator{
    ~ReadFileValidator() = default;

    bool isSupport(MetaInformation inf);

    bool validate(MetaInformation inf);
};



class WriteFileValidator: public Validator{
    ~WriteFileValidator() = default;

    bool isSupport(MetaInformation inf);

    bool validate(MetaInformation inf);
};



class GrepValidator: public Validator{
    ~GrepValidator() = default;

    bool isSupport(MetaInformation inf);

    bool validate(MetaInformation inf);
};



class SortValidator: public Validator{
    ~SortValidator() = default;

    bool isSupport(MetaInformation inf);

    bool validate(MetaInformation inf);
};



class ReplaceValidator: public Validator{
    ~ReplaceValidator() = default;

    bool isSupport(MetaInformation inf);

    bool validate(MetaInformation inf);
};



class DumpValidator: public Validator{
    ~DumpValidator() = default;

    bool isSupport(MetaInformation inf);

    bool validate(MetaInformation inf);
};

#endif
