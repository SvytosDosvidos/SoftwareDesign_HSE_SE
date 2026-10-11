#pragma once

#include "ObjectPark.h"

class StorageCenter {
public:
    void printObjectEasy() const;
    void printObjectNoEasy() const;

    void addObject(ObjectPark* objectPark);
private:
    std::vector<ObjectPark*> objectsEasy_;
    std::vector<ObjectPark*> objectsNoEasy_;
    Value cntElectrcity_;
};