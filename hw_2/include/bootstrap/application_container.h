#pragma once
#include "console_app.h"
#include "repository.h"

class ApplicationContainer {
public:
    ApplicationContainer();
    explicit ApplicationContainer(std::shared_ptr<IPOSRepository> repository);
    std::unique_ptr<POSApplicationFacade> facade() const;
    std::unique_ptr<ConsoleApp> console() const;
private:
    std::shared_ptr<IPOSRepository> repository_;
};
