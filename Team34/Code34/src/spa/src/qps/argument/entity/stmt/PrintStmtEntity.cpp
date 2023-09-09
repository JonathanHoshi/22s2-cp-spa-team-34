// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "PrintStmtEntity.h"
#include "common/ConversionUtils.h"
#include "qps/preprocessor/factory/entity/EntityCreator.h"

PrintStmtEntity::PrintStmtEntity(std::string name,
    std::string attrRef) : StmtEntity(name, attrRef) {}
PrintStmtEntity::PrintStmtEntity(IStmtGetter* pkbInterface,
    std::string name, std::string attrRef) : StmtEntity(pkbInterface, name, attrRef) {}

bool PrintStmtEntity::checkInstance(const Argument* ptr) {
    return dynamic_cast<const PrintStmtEntity*>(ptr) != nullptr;
}

std::unordered_set<std::string> PrintStmtEntity::getPKBValueList() {
    return ConversionUtils::convertIntToStringSet(pkbInterface->getPrintStmts());
}

std::string PrintStmtEntity::getAttrFromPKB(std::string id) {
    if (attrRef == EntityCreator::VARNAME_ATTR) {
        return pkbInterface->getPrintVar(stoi(id));
    }
    return id;
}

std::string PrintStmtEntity::getType() {
    return TYPE_NAME;
}
