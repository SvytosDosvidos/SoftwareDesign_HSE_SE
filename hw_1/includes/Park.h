#pragma once

#include <vector>

#include "ObjectPark.h"

using Value = long long;

class Park {
public:
    void AddObject(ObjectPark object);
private:
    std::vector<ObjectPark*> objectsEasy_;
    std::vector<ObjectPark*> objectsNoEasy_;
    Value cntElectrcity_;
};