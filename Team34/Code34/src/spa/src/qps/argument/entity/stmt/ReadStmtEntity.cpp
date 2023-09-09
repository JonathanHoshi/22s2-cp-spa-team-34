// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "ReadStmtEntity.h"
#include "common/ConversionUtils.h"
#include "qps/preprocessor/factory/entity/EntityCreator.h"

ReadStmtEntity::ReadStmtEntity(std::string name,
    std::string attrRef) : StmtEntity(name, attrRef) {}
ReadStmtEntity::ReadStmtEntity(IStmtGetter* pkbInterface,
    std::string name, std::string attrRef) : StmtEntity(pkbInterface, name, attrRef) {}

bool ReadStmtEntity::checkInstance(const Argument* ptr) {
    return dynamic_cast<const ReadStmtEntity*>(ptr) != nullptr;
}

std::unordered_set<std::string> ReadStmtEntity::getPKBValueList() {
    return ConversionUtils::convertIntToStringSet(pkbInterface->getReadStmts());
}

std::string ReadStmtEntity::getAttrFromPKB(std::string id) {
    if (attrRef == EntityCreator::VARNAME_ATTR) {
        return pkbInterface->getReadVar(stoi(id));
    }
    return id;
}

std::string ReadStmtEntity::getType() {
    return TYPE_NAME;
}
