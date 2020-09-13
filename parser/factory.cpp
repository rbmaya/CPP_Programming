#include "factory.h"

#include "ReaderWorker.h"
#include "WriteWorker.h"
#include "GrepWorker.h"
#include "SortWorker.h"
#include "ReplaceWorker.h"
#include "DumpWorker.h"

Factory::Factory(const MetaInformation & inf) : inf(inf) {}

Worker* Factory::createWorker() {
    if (inf.get_type() == "readfile"){
        return new ReaderWorker(inf.get_args());
    }

    if (inf.get_type() == "writefile"){
        return new WriteWorker(inf.get_args());
    }

    if (inf.get_type() == "grep"){
        return new GrepWorker(inf.get_args());
    }

    if (inf.get_type() == "sort"){
        return new SortWorker(inf.get_args());
    }

    if (inf.get_type() == "replace"){
        return new ReplaceWorker(inf.get_args());
    }

    if (inf.get_type() == "dump"){
        return new DumpWorker(inf.get_args());
    }

    return nullptr;
}