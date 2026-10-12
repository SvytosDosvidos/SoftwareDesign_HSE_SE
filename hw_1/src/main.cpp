#include <iostream>
#include <string>
#include <sstream>

#include "../includes/OwnerPark.h"

const int kMaxSymbols = 200;

std::stringstream getS() {
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
                std::string strError;
                std::cout << "Please input data:\n";
                std::stringstream input = getS();
                if(owner->addObject(input, strError)) {
                    std::cout << "The object has been created!!!\n";
                } else {
                    std::cout << "Incorrect data, because:\n";
                    std::cout << strError << "\n";
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