#include <iostream>
#include <string>
#include <sstream>

#include "../tests/catch.hpp"
#include "../includes/OwnerPark.h"

std::stringstream getS() {
    int maxSymbol = 200;
    std::string str;
    std::stringstream ss;
    while(std::cin && maxSymbol--) {
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
    std::stringstream ss = getS();
    int n;
    if(ss >> n) {
        return n;
    }

    return -1;
}

int main() {
    OwnerPark* owner = new OwnerPark();
    owner->printCommand();
    bool flagGontinue = true;

    while(flagGontinue) {
        int command_id = getCommand();

        switch(command_id) {
            case 1: {
                owner->printCommand();
                break;
            } case 2: {
                owner->printAllObjects();
                break;
            } case 3: {
                std::cout << "Please input data:\n";
                std::stringstream input = getS();
                if(owner->addObject(input)) {
                    std::cout << "Correct!\n";
                } else {
                    std::cout << "No!\n";
                }
                break;
            } case 4: {
                owner->printCommand4Add();
                break;
            } case 5: {
                flagGontinue = false;
            }
        }
    }

    delete owner;

    return 0;
}