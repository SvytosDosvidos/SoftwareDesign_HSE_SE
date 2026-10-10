#pragma once

#include <vector>

#include "ObjectPark.h"

using Value = long long;

class Park {
public:
    void printObjectEasy() const;
    void printObjectNoEasy() const;
    void addObject(ObjectPark object);
private:
    std::vector<ObjectPark> objectsEasy_;
    std::vector<ObjectPark> objectsNoEasy_;
    Value cntElectrcity_;
};