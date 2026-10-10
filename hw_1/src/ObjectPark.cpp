#include <iostream>

#include "../includes/ObjectPark.h"

void ObjectPark::printObject() const {
    std::cout << name_ << " " << inventoryId_ << " "
        << simplicity_ << " " << "\n"; //typeObject_ << "\n";
}