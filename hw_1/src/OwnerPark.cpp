#include <iostream>
#include <format>
#include <string>

#include "../includes/OwnerPark.h"

OwnerPark::OwnerPark() {
    init();
    park_ = new Park();
}

OwnerPark::~OwnerPark() {
    delete park_;
}

void OwnerPark::init() {
    mapCommand_["wheel"] = "[name][inventoryId]"
        "[simplicity][typeObject][typeWheel][radius]";
    mapCommand_["scooter electric"] = "[name]"
        "[inventoryId][simplicity][typeObject][electricityValue][inventoryIdWheel_1]"
            "[inventoryIdWheel_2][weigth]";
    mapCommand_["scooter"] = "[name][inventoryId]"
        "[simplicity][typeObject][inventoryIdWheel_1][inventoryIdWheel_2][weigth]";
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
    std::cout << std::format("+{:-^128}+\n", "");
    std::cout << std::format("|{: ^128}|\n", "Instructions on how to add an object:");
    std::cout << std::format("|{: ^128}|\n", "");

    std::cout << std::format("|{: ^128}|\n", "TypeObject:");
    std::cout << std::format("|{: ^128}|\n", "TransportElectric - 1");
    std::cout << std::format("|{: ^128}|\n", "TransportNoElectric - 2");
    std::cout << std::format("|{: ^128}|\n", "OtherElectric - 3");
    std::cout << std::format("|{: ^128}|\n", "SparePart - 4");
    std::cout << std::format("|{: ^128}|\n", "Other - 5");
    std::cout << std::format("|{: ^128}|\n", "");

    std::cout << std::format("|{: ^128}|\n", "TypeWheel:");
    std::cout << std::format("|{: ^128}|\n", "BicycleScooter - 1");
    std::cout << std::format("|{: ^128}|\n", "BicycleWheel - 2");
    std::cout << std::format("|{: ^128}|\n", "");

    for(const auto &it : mapCommand_) {
        std::cout <<  std::format("|{: ^128}|\n", it.first + " - " + it.second);
    }
    std::cout << std::format("+{:-^128}+\n", "");
}

void OwnerPark::printAllObjects() const {
    std::map<std::string, std::string> mapf;
    park_->printObjectEasy(mapCommand_);
    std::cout << "\n";
    park_->printObjectNoEasy(mapCommand_);
}

bool OwnerPark::addObject(std::stringstream& ss, std::string& strError) {
    bool flag = park_->addObject(ss, strError);
    return flag;
}