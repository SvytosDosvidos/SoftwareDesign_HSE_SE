#include <iostream>
#include <string>

#include "../tests/catch.hpp"
#include "../includes/OwnerPark.h"


std::string getS() {
    int maxSymbol = 200;
    std::string str;
    while(std::cin && maxSymbol--) {
        char c = std::cin.get();
        if(c == '\n') {
            break;
        }
        str.push_back(c);
    }

    return str;
}

int main() {
    OwnerPark* owner = new OwnerPark();
    owner->printCommand();

    while(true) {
        int command_id;
        std::cin >> command_id;

        switch(command_id) {
            case 1: {
                owner->printCommand();
                break;
            } case 2: {
                owner->printAllObjects();
                break;
            } case 3: {
                //getS();
            }
        }
    }

    delete owner;

    return 0;
}