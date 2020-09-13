#ifndef LAB2_MYEXCEPTION_H
#define LAB2_MYEXCEPTION_H

#include <exception>

class InpFileNotOpen: public std::exception{
public:
    const char* what() const noexcept;
};

class OutFileNotOpen: public std::exception{
public:
    const char* what() const noexcept;
};


class Unsupported: public std::exception{
public:
    const char* what() const noexcept;
};


class WrongArgs: public std::exception{
public:
    const char* what() const noexcept;
};

class WrongExecuters: public std::exception{
public:
    const char *what() const noexcept;
};


#endif
