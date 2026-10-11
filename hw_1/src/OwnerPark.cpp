#include <iostream>
#include <format>
#include <string>

#include "../includes/OwnerPark.h"

OwnerPark::OwnerPark() {
    park_ = new Park();
}

OwnerPark::~OwnerPark() {
    delete park_;
}

void OwnerPark::printCommand() const {
    std::cout << std::format("+{:-^48}+\n", "");
    std::cout << std::format("|{: ^48}|\n", "All command:");
    std::cout << std::format("|{: ^48}|\n", "");
    std::cout << std::format("|{: ^48}|\n", "1 - Display of all command");
    std::cout << std::format("|{: ^48}|\n", "2 - Display of all objects in the park");
    std::cout << std::format("|{: ^48}|\n", "3 - Add new object in the park");
    std::cout << std::format("|{: ^48}|\n", "4 - End program");
    std::cout << std::format("+{:-^48}+\n", "");
}

void OwnerPark::printCommand4Add() const {

}

void OwnerPark::printAllObjects() const {
    park_->printObjectEasy();
    park_->printObjectNoEasy();
}

bool OwnerPark::addObject(std::stringstream& ss) {
    bool flag = park_->addObject(ss);
    return flag;
}