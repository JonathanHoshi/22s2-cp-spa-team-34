// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "WildcardEntity.h"

WildcardEntity::WildcardEntity() : EntityArgument("", "") {}

bool WildcardEntity::checkInstance(const Argument* ptr) {
    return dynamic_cast<const WildcardEntity*>(ptr) != nullptr;
}

WildcardEntity* WildcardEntity::cast(Argument* ptr) {
    return dynamic_cast<WildcardEntity*>(ptr);
}

std::unordered_set<std::string> WildcardEntity::getPKBValueList() {
    return this->wildEntityType->getPKBValueList();
}

void WildcardEntity::assignEntityType(std::shared_ptr<EntityArgument> entityType) {
    this->wildEntityType = move(entityType);
}

void WildcardEntity::setPKBInterface(DI& di) {
    this->wildEntityType->setPKBInterface(di);
}

std::string WildcardEntity::getAttrFromPKB(std::string id) {
    throw std::runtime_error("Function should not be called");
}

std::string WildcardEntity::getType() {
    return TYPE_NAME;
}

bool WildcardEntity::operator==(const Argument& other) const {
    return false;
}
