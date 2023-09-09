// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "AssignStmtEntity.h"
#include "common/ConversionUtils.h"

AssignStmtEntity::AssignStmtEntity(std::string name,
    std::string attrRef) : StmtEntity(name, attrRef) {}

AssignStmtEntity::AssignStmtEntity(IStmtGetter* pkbInterface, std::string name,
    std::string attrRef) : StmtEntity(pkbInterface, name, attrRef) {}

bool AssignStmtEntity::checkInstance(const Argument* ptr) {
    return dynamic_cast<const AssignStmtEntity*>(ptr) != nullptr;
}

bool AssignStmtEntity::checkType(const EntityArgument* ptr) {
    return typeid(AssignStmtEntity) == typeid(*ptr);
}

std::unordered_set<std::string> AssignStmtEntity::getPKBValueList() {
    return ConversionUtils::convertIntToStringSet(pkbInterface->getAssignStmts());
}

std::string AssignStmtEntity::getType() {
    return TYPE_NAME;
}
