#include <iostream>

#include "../includes/Park.h"

void Park::printObjectEasy() const {
    for(const auto &it : objectsEasy_) {
        it.printObject();
    }
}

void Park::printObjectNoEasy() const {
    for(const auto &it : objectsNoEasy_) {
        it.printObject();
    }
}