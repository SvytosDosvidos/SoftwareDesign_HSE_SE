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
    std::cout << std::format("|{: ^48}|\n", "1 - Instructions for all commands");
    std::cout << std::format("|{: ^48}|\n", "2 - Display of all objects in the park");
    std::cout << std::format("|{: ^48}|\n", "3 - Add new object in the park");
    std::cout << std::format("|{: ^48}|\n", "4 - Instructions on how to add an object");
    std::cout << std::format("|{: ^48}|\n", "5 - End program");
    std::cout << std::format("+{:-^48}+\n", "");
}

void OwnerPark::printCommand4Add() const {
    std::cout << std::format("+{:-^108}+\n", "");
    std::cout << std::format("|{: ^108}|\n", "Instructions on how to add an object:");
    std::cout << std::format("|{: ^108}|\n", "");

    std::cout << std::format("|{: ^108}|\n", "TypeObject:");
    std::cout << std::format("|{: ^108}|\n", "TransportElectric - 1");
    std::cout << std::format("|{: ^108}|\n", "TransportNoElectric - 2");
    std::cout << std::format("|{: ^108}|\n", "OtherElectric - 3");
    std::cout << std::format("|{: ^108}|\n", "SparePart - 4");
    std::cout << std::format("|{: ^108}|\n", "Other - 5");
    std::cout << std::format("|{: ^108}|\n", "");

    std::cout << std::format("|{: ^108}|\n", "TypeWheel:");
    std::cout << std::format("|{: ^108}|\n", "BicycleScooter - 1");
    std::cout << std::format("|{: ^108}|\n", "BicycleWheel - 2");
    std::cout << std::format("|{: ^108}|\n", "");

    std::cout << std::format("|{: ^108}|\n", "Wheel - [name][inventoryId][simplicity]"
        "[typeObject][typeWheel][radius]");
    std::cout << std::format("|{: ^108}|\n", "Scooter - [name][inventoryId][simplicity]"
        "[typeObject][inventoryIdWheel_1][inventoryIdWheel_2][weigth]");
    std::cout << std::format("+{:-^108}+\n", "");
}

void OwnerPark::printAllObjects() const {
    park_->printObjectEasy();
    park_->printObjectNoEasy();
}

bool OwnerPark::addObject(std::stringstream& ss) {
    bool flag = park_->addObject(ss);
    return flag;
}