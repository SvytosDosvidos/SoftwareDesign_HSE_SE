#pragma once

#include <memory>
#include <typeindex>
#include <unordered_map>
#include <stdexcept>
#include <string>

class DIContainer {
public:
    DIContainer() = default;

    template<typename Interface>
    void registerInstance(std::shared_ptr<Interface> instance) {
        services_[std::type_index(typeid(Interface))] = instance;
    }

    template<typename Interface, typename Implementation, typename... Args>
    void registerSingleton(Args&&... args) {
        auto instance = std::make_shared<Implementation>(std::forward<Args>(args)...);
        services_[std::type_index(typeid(Interface))] = instance;
    }

    template<typename Interface>
    std::shared_ptr<Interface> resolve() const {
        auto it = services_.find(std::type_index(typeid(Interface)));
        if (it == services_.end()) {
            throw std::runtime_error("Service not registered in DI container: " +
                                     std::string(typeid(Interface).name()));
        }
        return std::static_pointer_cast<Interface>(it->second);
    }

    template<typename Interface>
    bool has() const {
        return services_.find(std::type_index(typeid(Interface))) != services_.end();
    }

private:
    std::unordered_map<std::type_index, std::shared_ptr<void>> services_;
};