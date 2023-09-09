// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "WhileStmtEntity.h"
#include "common/ConversionUtils.h"

WhileStmtEntity::WhileStmtEntity(std::string name,
    std::string attrRef) : StmtEntity(name, attrRef), PatternSynonym() {}
WhileStmtEntity::WhileStmtEntity(IStmtGetter* pkbInterface,
    std::string name, std::string attrRef) :
    StmtEntity(pkbInterface, name, attrRef), PatternSynonym() {}

bool WhileStmtEntity::checkInstance(const Argument* ptr) {
    return dynamic_cast<const WhileStmtEntity*>(ptr) != nullptr;
}

std::unordered_set<std::string> WhileStmtEntity::getPKBValueList() {
    return ConversionUtils::convertIntToStringSet(pkbInterface->getWhileStmts());
}

std::string WhileStmtEntity::getType() {
    return TYPE_NAME;
}
