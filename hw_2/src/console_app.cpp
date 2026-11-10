#include "../include/console_app.h"

#include<iostream>
#include<format>
#include<sstream>
#include<string>

ConsoleApp::ConsoleApp() {
    posApplicationFacade_ = std::make_unique<POSApplicationFacade>();
}

constexpr int kMaxSymbols = 200;

std::stringstream getStr() {
    std::string str;
    std::stringstream ss;

    while(std::cin && str.size() < kMaxSymbols) {
        char c = std::cin.get();
        if(c == '\n') {
            break;
        }
        str.push_back(c);
    }

    ss << str;
    return ss;
}

int getCommand() {
    std::stringstream ss = getStr();
    int n;
    if(ss >> n) {
        return n;
    }
    return -1;
}

void ConsoleApp::run() {
    bool isWorkProgram = true;
    printCommand();

    while(isWorkProgram) {
        int idCommand = getCommand();

        switch (idCommand) {
            case 1: {
                printCommand();
                break;
            } case 2: {
                printStudents();
                break;
            } case 3: {
                printLecturers();
                break;
            } case 4: {

                break;
            } case 5: {

                break;
            } default: {
                std::cout << "Unknown command!\n";
                break;
            }
        }
    }
}

void ConsoleApp::printCommand() const {
    std::cout << std::format("+{:-^78}+\n", "");
    std::cout << std::format("|{: ^78}|\n", "All command:");
    std::cout << std::format("|{: ^78}|\n", "");
    std::cout << std::format("|{: ^78}|\n", "1 - Instructions for all commands");
    std::cout << std::format("|{: ^78}|\n", "2 - Displaying the entire students in the university");
    std::cout << std::format("|{: ^78}|\n", "3 - Displaying the entire lecturer, and what they teach");
    std::cout << std::format("|{: ^78}|\n", "4 - Add new student/lecturer/manager in university");
    std::cout << std::format("|{: ^78}|\n", "5 - Instructions on how to add student/lecturer/manager");
    std::cout << std::format("|{: ^78}|\n", "6 - End program");
    std::cout << std::format("+{:-^78}+\n", "");
}

void ConsoleApp::printCommand4Add() const {

}

void ConsoleApp::printStudents() const {
    posApplicationFacade_->printStudents();
}

void ConsoleApp::printLecturers() const {
    posApplicationFacade_->printLecturers();
}