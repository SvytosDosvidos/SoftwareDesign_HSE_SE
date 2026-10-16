#pragma once

#include <iostream>
#include <optional>
#include <map>
#include <string>
#include <vector>
#include <sstream>

#include "ObjectPark.h"

class StorageCenter {
public:
    StorageCenter();
    void init();

    void printObjectEasy(const std::map<std::string, std::string>& mapCommand) const;
    void printObjectNoEasy(const std::map<std::string, std::string>& mapCommand) const;

    void addObject(IInventoryItem* objectPark);
    std::optional<IInventoryItem*> getObject(const std::string& name, int inventoryId);

    void deleteObject(int inventoryId);

    bool checkSimplicity(int simplicity, std::string& strError) const;
    bool checkUniqueId(int inventoryId, std::string& strError) const;
    bool checkCntElectrcity(Value cntElectrcity, std::string& strError) const;
    bool checkTypeObject(const std::string& name, TypeObject typeObject, std::string& strError) const;

    void addCntElectrcity(Value cntElectrcity);
    Value getCntElectrcity() const;

private:
    void printObject(const std::vector<BaseRentable*>& objects,
        const std::map<std::string, std::string>& mapCommand) const;

    std::vector<BaseRentable*> objectsEasy_;
    std::vector<BaseRentable*> objectsNoEasy_;
    std::vector<IInventoryItem*> other_;
    Value cntElectrcity_;

    std::vector<std::string> orderPrint_ = {"wheel", "scooter", "scooter_electric"};
    std::map<std::string, TypeObject> types_;
};