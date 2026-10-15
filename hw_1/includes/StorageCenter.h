#pragma once

#include <iostream>
#include <optional>
#include <map>
#include <string>
#include <sstream>

#include "ObjectPark.h"

class StorageCenter {
public:
    StorageCenter();

    void init();

    void printObjectEasy(const std::map<std::string, std::string>& mapCommand) const;
    void printObjectNoEasy(const std::map<std::string, std::string>& mapCommand) const;

    void addObject(IInventoryItem* objectPark);
    std::optional<IInventoryItem*> getObject(std::string&& name, int inventoryId,
        int simplicity);

    void deleteObject(int inventoryId);

    bool checkSimplicity(int simplicity, std::string& strError) const;
    bool checkUniqueId(int inventoryId, std::string& strError) const;
    bool checkCntElectrcity(Value cntElectrcity, std::string& strError) const;
    bool checkTypeObject(std::string&& name, TypeObject typeObject, std::string& strError) const;

    void addCntElectrcity(Value cntElectrcity);
    Value getCntElectrcity() const;
private:

    void printObject(const std::vector<IInventoryItem*> objects,
        const std::map<std::string, std::string>& mapCommand) const;

    bool checkUniqueId(const std::vector<IInventoryItem*>& objects,
        int inventoryId, std::string& strError) const;

    int simplicityMin_ = 6;

    std::vector<IInventoryItem*> objectsEasy_;
    std::vector<IInventoryItem*> objectsNoEasy_;
    Value cntElectrcity_;

    std::vector<std::string> orderPrint_ = {"wheel", "scooter", "scooter electric"};
    std::map<std::string, TypeObject> types_;
};