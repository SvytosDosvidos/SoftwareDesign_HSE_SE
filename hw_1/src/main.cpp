#include <iostream>
#include <string>

#include "../includes/OwnerPark.h"

void getS() {
    int maxSymbol = 200;
    std::string str;
    while(std::cin && maxSymbol--) {
        char c = std::cin.get_c();
        if(c == '\n') {
            break;
        }
        str.push_back(c);
    }

    return str;
}

int main() {
    OwnerPark owner = OwnerPark();

    while(true) {
        int command_id;
        owner.printCommand();
        std::cin >> command_id;

        switch(command_id) {
            case 1: {
                owner.printCommand();
                break;
            } case 2: {
                owner.printObjects();
                break;
            } case 3: {
                getS();
            }
        }
    }
    return 0;
}