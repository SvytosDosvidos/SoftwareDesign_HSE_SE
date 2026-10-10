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
    std::cout << std::format("+{:-^48}+\n", "");
}

void OwnerPark::printObjects() const {
    for(const auto &it : objectsEasy_) {
        std::cout << it->name_ << " " << it->inventoryId_ << " "
            << it->simplicity_ << " " << it->typeObject_ << "\n";
    }
}