#pragma once

#include <string>
#include "ObjectPark.h"

class IServiceCenter {
public:
    virtual ~IServiceCenter() = default;
    virtual bool inspect(const IInventoryItem& item, std::string& strError) = 0;
};

class StandardServiceCenter : public IServiceCenter {
public:
    bool inspect(const IInventoryItem& item, std::string& strError) override;
};