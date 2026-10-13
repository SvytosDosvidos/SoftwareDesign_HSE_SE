#pragma once

#include <vector>
#include <map>
#include <string>

#include "ObjectPark.h"
#include "CreatorObject.h"

using Value = long long;

class Park {
public:
    Park();

    void printObjectEasy(const std::map<std::string, std::string>& mapCommand) const;
    void printObjectNoEasy(const std::map<std::string, std::string>& mapCommand) const;
    bool addObject(std::stringstream& ss, std::string& strError);

    Value getCntElectricity() const;
private:
    CreatorObject* creatorObject_;
    StorageCenter* storageCenter_;
};