// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once

#include <memory>
#include <stdexcept>
#include <typeindex>
#include <unordered_map>

#include "IService.h"

class DI {
private:
    std::unordered_map<std::type_index, std::shared_ptr<IService>> diServices;

public:
    template <typename Interface, typename Implementation>

    void registerService(std::shared_ptr<Implementation> service) {
        if (!std::is_base_of_v<Interface, Implementation>) {
            throw std::invalid_argument("Interface not implemented");
        }
        diServices[std::type_index(typeid(Interface))] =
            std::static_pointer_cast<IService>(service);
    }

    template <typename Interface> Interface& getService() {
        auto found = diServices.find(std::type_index(typeid(Interface)));
        if (found == diServices.end()) {
            throw std::runtime_error("Service not registered");
        }
        return *dynamic_cast<Interface*>(found->second.get());
    }
};
