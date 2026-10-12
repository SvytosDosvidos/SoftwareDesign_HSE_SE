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

    bool checkSimplicity(int simplicity, std::string& strError) const;
    bool checkUniqueId(int inventoryId, std::string& strError) const;
    bool checkCntElectrcity(Value cntElectrcity, std::string& strError) const;

    void addCntElectrcity(Value cntElectrcity);
private:
    int simplicityMin_ = 6;

    std::vector<ObjectPark*> objectsEasy_;
    std::vector<ObjectPark*> objectsNoEasy_;
    Value cntElectrcity_;
};