#pragma once

#include "Park.h"

class OwnerPark {
public:
    OwnerPark();
    ~OwnerPark();

    void printCommand() const;
    void printObjects() const;
private:
    Park* park_;
};