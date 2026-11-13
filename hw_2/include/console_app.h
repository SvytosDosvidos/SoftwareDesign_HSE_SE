#pragma once

#include "pos_application_facade.h"

#include<memory>
#include<unordered_map>
#include<sstream>

using creator = std::function<void(std::stringstream&, std::string&)>;
using binder = std::function<void(std::stringstream&, std::string&)>;

class ConsoleApp {
public:
    ConsoleApp();

    void init();
    void run();

    std::string execute(std::stringstream& input);

    void printStudents() const;
    void printLecturers() const;

    void printCommand() const;
    void printCommand4Add() const;
private:
    std::unique_ptr<POSApplicationFacade> posApplicationFacade_;
    std::unordered_map<std::string, std::string> map4Print_;
    std::unordered_map<std::string, creator> mapCreator_;
    std::unordered_map<std::string, binder> mapBinder_;
};