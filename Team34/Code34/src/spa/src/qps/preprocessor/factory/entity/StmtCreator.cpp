// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include <unordered_set>
#include "StmtCreator.h"
#include "qps/argument/entity/stmt/StmtStmtEntity.h"

StmtCreator::StmtCreator() : EntityCreator() {
    validAttrRefs = std::unordered_set<std::string>({STMT_ATTR});
}

std::shared_ptr<EntityArgument> StmtCreator::create(std::string name) {
    return std::make_shared<StmtStmtEntity>(name, STMT_ATTR);
}

std::shared_ptr<EntityArgument> StmtCreator::create(std::string name, std::string attrRef) {
    return std::make_shared<StmtStmtEntity>(name, isAttrRefValid(validAttrRefs, attrRef));
}
