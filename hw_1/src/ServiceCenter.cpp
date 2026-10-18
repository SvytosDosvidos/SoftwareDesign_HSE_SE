#include "../includes/ServiceCenter.h"

bool StandardServiceCenter::inspect(const IInventoryItem& item, std::string& strError) {
    if(item.getInventoryId() <= 0) {
        strError += "Inspection failed: InventoryId must be positive\n";
        return false;
    }

    if(const auto* rentable = dynamic_cast<const IRentable*>(&item)) {
        if(rentable->getSimplicity() < 1 || rentable->getSimplicity() > 10) {
            strError += "Inspection failed: Simplicity score must be between 1 and 10\n";
            return false;
        }
    }

    if(const auto* consumer = dynamic_cast<const IEnergyConsumer*>(&item)) {
        if(consumer->getDailyEnergyConsumption() <= 0) {
            strError += "Inspection failed: Daily energy consumption must be positive\n";
            return false;
        }
        if(consumer->getDailyEnergyConsumption() > 10000) {
            strError += "Inspection failed: Suspiciously high energy consumption (battery issue)\n";
            return false;
        }
    }

    return true;
}