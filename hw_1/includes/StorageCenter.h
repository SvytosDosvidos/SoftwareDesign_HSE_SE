#pragma once

#include <optional>

#include "ObjectPark.h"

class StorageCenter {
public:
    StorageCenter();

    void printObjectEasy() const;
    void printObjectNoEasy() const;

    void addObject(ObjectPark* objectPark);
    std::optional<ObjectPark*> getObject(std::string name, int inventoryId,
        int simplicity);
private:
    int simplicityMin = 6;

    std::vector<ObjectPark*> objectsEasy_;
    std::vector<ObjectPark*> objectsNoEasy_;
    Value cntElectrcity_;
};