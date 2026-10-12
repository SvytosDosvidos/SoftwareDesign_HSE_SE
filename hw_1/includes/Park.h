#pragma once

#include <vector>

#include "ObjectPark.h"
#include "CreatorObject.h"

using Value = long long;

class Park {
public:
    Park();

    void printObjectEasy() const;
    void printObjectNoEasy() const;
    bool addObject(std::stringstream& ss, std::string& strError);
private:
    CreatorObject* creatorObject_;
    StorageCenter* storageCenter_;
};