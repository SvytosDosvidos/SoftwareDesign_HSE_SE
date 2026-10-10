#include <iostream>

#include "../includes/OwnerPark.h"

OwnerPark::OwnerPark() {
    park_ = new Park();
}

OwnerPark::~OwnerPark() {
    delete park_;
}

void OwnerPark::printCommand() {
    std::cout << "All command:\n";

    std::cout << "1 - add Object\n";
}