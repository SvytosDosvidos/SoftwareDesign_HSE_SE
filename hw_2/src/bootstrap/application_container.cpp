#include "bootstrap/application_container.h"
#include <stdexcept>

ApplicationContainer::ApplicationContainer() : ApplicationContainer(std::make_shared<InMemoryPOSRepository>()) {}
ApplicationContainer::ApplicationContainer(std::shared_ptr<IPOSRepository> repository)
    : repository_(std::move(repository)) {
    if(!repository_) throw std::invalid_argument("repository must not be null");
}
std::unique_ptr<POSApplicationFacade> ApplicationContainer::facade() const {
    return std::make_unique<POSApplicationFacade>(repository_);
}
std::unique_ptr<ConsoleApp> ApplicationContainer::console() const {
    return std::make_unique<ConsoleApp>(facade());
}
// Compatibility constructors for the original public API; wiring stays at the edge.
POSApplicationFacade::POSApplicationFacade() : POSApplicationFacade(std::make_shared<InMemoryPOSRepository>()) {}
ConsoleApp::ConsoleApp() : ConsoleApp(ApplicationContainer().facade()) {}
