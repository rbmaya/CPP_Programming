#include "scheme.h"
#include "factory.h"
#include <iostream>
#include "validator.h"
#include <map>


void Scheme::add_Worker(const MetaInformation &inf) {
    Factory factory(inf);
    auto it = workers.find(inf.get_id());
    if ((it->second != nullptr)) throw WrongExecuters();
    workers[inf.get_id()] = factory.createWorker();
}


void Scheme::add_executers(const std::vector <std::string> & numbers) {
    std::map <int, bool> check;
    try {
        for (auto &val : numbers) {
            int number = std::stoi(val);
            if ((number < 0) || (check[number])) throw WrongExecuters();
            auto it = workers.find(number);
            if (it == workers.end()) throw WrongExecuters();

            if (val == *numbers.begin()) {
                if (workers[number]->get_type() != "readfile") throw WrongExecuters();
            } else if (workers[number]->get_type() == "readfile") throw WrongExecuters();

            if (val == *(numbers.end() - 1)) {
                if (workers[number]->get_type() != "writefile") throw WrongExecuters();
            } else if (workers[number]->get_type() == "writefile") throw WrongExecuters();

            executers.push_back(std::stoi(val));
            check[number] = true;
        }
    }

    catch (const std::exception & exc){
        std::cerr << "Error! " << exc.what() << std::endl;
        throw EXIT_FAILURE;
    }

}


void Scheme::process() {
    auto *inp_text = new std::vector <std::string>;

    for (auto & val: executers) {
        try {
            if (!workers[val]) {
                throw WrongExecuters();
            }
            *inp_text = workers[val]->process(*inp_text);
        }
        catch(const std::exception & exc){
            std::cerr << "Error! " << exc.what() << std::endl;
            delete inp_text;
            throw EXIT_FAILURE;
        }
        catch (int exc) {
            delete inp_text;
            throw EXIT_FAILURE;
        }
    }

    delete inp_text;

    for (auto &it : workers)
        delete it.second;

}
