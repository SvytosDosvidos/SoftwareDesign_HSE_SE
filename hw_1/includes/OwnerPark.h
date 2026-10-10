#pragma once

#include "Park.h"

class OwnerPark {
private:
    OwnerPark();
    ~OwnerPark();

    void printCommand();
public:
    Park* park_;
};