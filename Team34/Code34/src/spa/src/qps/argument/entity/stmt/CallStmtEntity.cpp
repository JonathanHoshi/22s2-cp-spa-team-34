// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "CallStmtEntity.h"
#include "common/ConversionUtils.h"
#include "qps/preprocessor/factory/entity/EntityCreator.h"

CallStmtEntity::CallStmtEntity(std::string name, std::string attrRef) : StmtEntity(name, attrRef) {}
CallStmtEntity::CallStmtEntity(IStmtGetter* pkbInterface, std::string name,
    std::string attrRef) : StmtEntity(pkbInterface, name, attrRef) {}

bool CallStmtEntity::checkInstance(const Argument* ptr) {
    return dynamic_cast<const CallStmtEntity*>(ptr) != nullptr;
}

std::unordered_set<std::string> CallStmtEntity::getPKBValueList() {
    return ConversionUtils::convertIntToStringSet(pkbInterface->getCallStmts());
}

std::string CallStmtEntity::getAttrFromPKB(std::string id) {
    if (attrRef == EntityCreator::PROCNAME_ATTR) {
        return pkbInterface->getCallProc(stoi(id));
    }
    return id;
}

std::string CallStmtEntity::getType() {
    return TYPE_NAME;
}
