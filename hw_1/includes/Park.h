#pragma once

#include <vector>
#include <map>
#include <string>
#include <memory>

#include "ObjectPark.h"
#include "CreatorObject.h"
#include "ServiceCenter.h"

using Value = long long;

class Park {
public:
    explicit Park(std::shared_ptr<IServiceCenter> serviceCenter);

    Park();
    ~Park();

    void printObjectEasy(const std::map<std::string, std::string>& mapCommand) const;
    void printObjectNoEasy(const std::map<std::string, std::string>& mapCommand) const;
    bool addObject(std::stringstream& ss, std::string& strError);

    Value getCntElectricity() const;

private:
    CreatorObject* creatorObject_;
    StorageCenter* storageCenter_;
    std::shared_ptr<IServiceCenter> serviceCenter_;
};