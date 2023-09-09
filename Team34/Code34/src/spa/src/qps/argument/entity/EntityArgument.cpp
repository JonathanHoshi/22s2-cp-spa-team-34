// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "EntityArgument.h"

EntityArgument::EntityArgument(std::string input, std::string attrRef) : Argument(input) {
    this->attrRef = attrRef;
}

bool EntityArgument::checkInstance(const Argument* ptr) {
    return dynamic_cast<const EntityArgument*>(ptr) != nullptr;
}

std::string EntityArgument::getAttrRef() {
    return this->attrRef;
}

EntityArgument* EntityArgument::cast(Argument* ptr) {
    return dynamic_cast<EntityArgument*>(ptr);
}
