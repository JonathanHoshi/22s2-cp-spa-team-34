// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "StmtEntity.h"
#include "common/ConversionUtils.h"

void StmtEntity::setPKBInterface(IStmtGetter* pkbInterface) {
    this->pkbInterface = pkbInterface;
}

StmtEntity::StmtEntity(std::string name,
    std::string attrRef) : StmtEntity(nullptr, name, attrRef) {}

StmtEntity::StmtEntity(IStmtGetter* pkbInterface,
    std::string name, std::string attrRef) : EntityArgument(name, attrRef) {
    setPKBInterface(pkbInterface);
}

bool StmtEntity::checkInstance(const Argument* ptr) {
    return dynamic_cast<const StmtEntity*>(ptr) != nullptr;
}

std::unordered_set<std::string> StmtEntity::getPKBValueList() {
    return ConversionUtils::convertIntToStringSet(pkbInterface->getAllStmts());
}

void StmtEntity::setPKBInterface(DI& di) {
    setPKBInterface(&di.getService<IStmtGetter>());
}

std::string StmtEntity::getAttrFromPKB(std::string id) {
    return id;
}

std::string StmtEntity::getType() {
    return TYPE_NAME;
}
