// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.
#include <unordered_set>
#include "AssignCreator.h"

AssignCreator::AssignCreator() : EntityCreator() {
    validAttrRefs = std::unordered_set<std::string>({STMT_ATTR});
}

std::shared_ptr<EntityArgument> AssignCreator::create(std::string name) {
    return std::make_shared<AssignStmtEntity>(name, STMT_ATTR);
}

std::shared_ptr<EntityArgument> AssignCreator::create(std::string name, std::string attrRef) {
    return std::make_shared<AssignStmtEntity>(name, isAttrRefValid(validAttrRefs, attrRef));
}
