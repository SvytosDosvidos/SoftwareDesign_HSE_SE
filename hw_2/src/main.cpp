#include <iostream>
#include <memory>
#include <sstream>

#include "../include/parser.h"
#include "../include/university.h"

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

int main() {
    std::unique_ptr<Parser> parser = std::make_unique<Parser>();
    std::unique_ptr<University> university = std::make_unique<University>();
    while(true) {
        int idCommand = getCommand();

        switch (idCommand) {
            case 1: {

            } case 2: {

            } case 3: {

            } default: {

            }
        }
    }
}