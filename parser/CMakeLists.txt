cmake_minimum_required(VERSION 3.15)
project(lab2)

set(CMAKE_CXX_STANDARD 14)

add_executable(lab2 main.cpp worker.cpp worker.h parser.cpp parser.h validator.cpp validator.h ReaderWorker.cpp ReaderWorker.h myException.h scheme.cpp scheme.h factory.cpp factory.h WriteWorker.cpp WriteWorker.h GrepWorker.cpp GrepWorker.h SortWorker.cpp SortWorker.h ReplaceWorker.cpp ReplaceWorker.h DumpWorker.cpp DumpWorker.h myException.cpp tests.cpp)