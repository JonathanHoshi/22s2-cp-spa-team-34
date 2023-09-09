// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "IfStmtEntity.h"
#include "common/ConversionUtils.h"

IfStmtEntity::IfStmtEntity(std::string name, std::string attrRef) : StmtEntity(name, attrRef),
PatternSynonym() {}
IfStmtEntity::IfStmtEntity(IStmtGetter* pkbInterface, std::string name, std::string attrRef) :
    StmtEntity(pkbInterface, name, attrRef), PatternSynonym() {}

bool IfStmtEntity::checkInstance(const Argument* ptr) {
    return dynamic_cast<const IfStmtEntity*>(ptr) != nullptr;
}

std::unordered_set<std::string> IfStmtEntity::getPKBValueList() {
    return ConversionUtils::convertIntToStringSet(pkbInterface->getIfStmts());
}

std::string IfStmtEntity::getType() {
    return TYPE_NAME;
}
