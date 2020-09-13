#include "myException.h"

const char* InpFileNotOpen::what() const noexcept {
    return "Input file did not open.";
}

const char* OutFileNotOpen::what() const noexcept {
    return "Output file did not open.";
}

const char* Unsupported::what() const noexcept {
    return "Block format is not supported.";
}

const char* WrongArgs::what() const noexcept {
    return "Wrong set of arguments for the block.";
}

const char* WrongExecuters::what() const noexcept{
    return "Wrong set of executers.";
}