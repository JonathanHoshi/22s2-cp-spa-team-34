// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "ConstantEntity.h"
#include "common/ConversionUtils.h"

void ConstantEntity::setPKBInterface(IConstGetter* pkbInterface) {
    this->pkbInterface = pkbInterface;
}

ConstantEntity::ConstantEntity(std::string value,
    std::string attrRef) : ConstantEntity(nullptr, value, attrRef) {}

ConstantEntity::ConstantEntity(IConstGetter* pkbInterface,
    std::string value, std::string attrRef) : EntityArgument(value, attrRef) {
    setPKBInterface(pkbInterface);
}

bool ConstantEntity::checkInstance(const Argument* ptr) {
    return dynamic_cast<const ConstantEntity*>(ptr) != nullptr;
}

std::unordered_set<std::string> ConstantEntity::getPKBValueList() {
    return ConversionUtils::convertIntToStringSet(pkbInterface->getConsts());
}

void ConstantEntity::setPKBInterface(DI& di) {
    setPKBInterface(&di.getService<IConstGetter>());
}

std::string ConstantEntity::getAttrFromPKB(std::string id) {
    return id;
}

std::string ConstantEntity::getType() {
    return TYPE_NAME;
}
