#pragma once

#include "pos_application_facade.h"

#include<memory>

class ConsoleApp {
public:
    ConsoleApp();

    void run();

    void printStudents() const;
    void printLecturers() const;

    void printCommand() const;
    void printCommand4Add() const;
private:
    std::unique_ptr<POSApplicationFacade> posApplicationFacade_;
};