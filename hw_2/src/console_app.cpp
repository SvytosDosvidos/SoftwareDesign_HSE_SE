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

void ConsoleApp::init() {
    mapCommand_["student"] = "[idPass][name]";
    mapCommand_["lecturer"] = "[idPass][name]";
    mapCommand_["subject"] = "[name][]";
}

void ConsoleApp::run() {
    bool isWorkProgram = true;
    init();
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
                std::string strError;
                std::cout << "Input data:\n";
                std::stringstream input = getS();
                if(owner->addObject(input, strError)) {
                    std::cout << "The object has been created!!!\n";
                } else {
                    std::cout << "Incorrect data, because:\n";
                    std::cout << strError << "\n";
                }
                break;
            } case 5: {
                printCommand4Add();
                break;
            } case 6: {
                isWorkProgram = false;
                break;
            } default: {
                std::cout << "Unknown command!\n";
                break;
            }
        }
    }
}

std::string ConsoleApp::execute(std::stringstream input) {
    std::string name;
    input >> name;

    std::string errorStr;
    if(mapCommand_[name] == mapCommand_.end()) {
        errorStr = "Invalid name for add object";
        return errorStr;
    }


}

void ConsoleApp::printCommand() const {
    std::cout << std::format("+{:-^128}+\n", "");
    std::cout << std::format("|{: ^128}|\n", "All command:");
    std::cout << std::format("|{: ^128}|\n", "");
    std::cout << std::format("|{: ^78}|\n", "1 - Instructions for all commands");
    std::cout << std::format("|{: ^128}|\n", "2 - Displaying the entire students in the university");
    std::cout << std::format("|{: ^128}|\n", "3 - Displaying the entire lecturer, and what they teach");
    std::cout << std::format("|{: ^128}|\n", "4 - Add new student/lecturer/subject/educationDirection in university");
    std::cout << std::format("|{: ^128}|\n", "5 - Instructions on how to add student/lecturer/subject/educationDirection");
    std::cout << std::format("|{: ^128}|\n", "6 - End program");
    std::cout << std::format("+{:-^128}+\n", "");
}

void ConsoleApp::printCommand4Add() const {
    std::cout << std::format("+{:-^128}+\n", "");
    std::cout << std::format("|{: ^128}|\n", "Instructions on how to add an object:");
    std::cout << std::format("|{: ^128}|\n", "");

    /*std::cout << std::format("|{: ^128}|\n", "TypeObject:");
    std::cout << std::format("|{: ^128}|\n", "TransportElectric - 1");
    std::cout << std::format("|{: ^128}|\n", "TransportNoElectric - 2");
    std::cout << std::format("|{: ^128}|\n", "OtherElectric - 3");
    std::cout << std::format("|{: ^128}|\n", "SparePart - 4");
    std::cout << std::format("|{: ^128}|\n", "Other - 5");
    std::cout << std::format("|{: ^128}|\n", "");

    std::cout << std::format("|{: ^128}|\n", "TypeWheel:");
    std::cout << std::format("|{: ^128}|\n", "ScooterWheel - 1");
    std::cout << std::format("|{: ^128}|\n", "BicycleWheel - 2");
    std::cout << std::format("|{: ^128}|\n", "");*/

    for(const auto &it : mapCommand_) {
        std::cout << std::format("|{: ^128}|\n", it.first + " - " + it.second);
    }
}

void ConsoleApp::printStudents() const {
    posApplicationFacade_->printStudents();
}

void ConsoleApp::printLecturers() const {
    posApplicationFacade_->printLecturers();
}