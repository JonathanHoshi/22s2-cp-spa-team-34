// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "VariableEntity.h"

void VariableEntity::setPKBInterface(IVarGetter* pkbInterface) {
    this->pkbInterface = pkbInterface;
}

VariableEntity::VariableEntity(std::string name,
    std::string attrRef) : VariableEntity(nullptr, name, attrRef) {}

VariableEntity::VariableEntity(IVarGetter* pkbInterface,
    std::string name, std::string attrRef) : EntityArgument(name, attrRef) {
    setPKBInterface(pkbInterface);
}

bool VariableEntity::checkInstance(const Argument* ptr) {
    return dynamic_cast<const VariableEntity*>(ptr) != nullptr;
}


std::unordered_set<std::string> VariableEntity::getPKBValueList() {
    return pkbInterface->getVars();
}

void VariableEntity::setPKBInterface(DI& di) {
    setPKBInterface(&di.getService<IVarGetter>());
}

std::string VariableEntity::getAttrFromPKB(std::string id) {
    return id;
}

std::string VariableEntity::getType() {
    return TYPE_NAME;
}
