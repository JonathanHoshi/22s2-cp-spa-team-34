// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "StmtStmtEntity.h"
#include "common/ConversionUtils.h"
#include "qps/preprocessor/factory/entity/EntityCreator.h"

StmtStmtEntity::StmtStmtEntity(std::string name,
                               std::string attrRef) : StmtEntity(name, attrRef) {}
StmtStmtEntity::StmtStmtEntity(IStmtGetter* pkbInterface,
                               std::string name, std::string attrRef) :
                               StmtEntity(pkbInterface, name, attrRef) {}

bool StmtStmtEntity::checkInstance(const Argument* ptr) {
    return dynamic_cast<const StmtStmtEntity*>(ptr) != nullptr;
}

bool StmtStmtEntity::checkType(const EntityArgument* ptr) {
    return typeid(StmtStmtEntity) == typeid(*ptr);
}
