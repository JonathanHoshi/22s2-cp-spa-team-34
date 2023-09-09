// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.
#include <unordered_set>
#include "IfCreator.h"

IfCreator::IfCreator() : EntityCreator() {
    validAttrRefs = std::unordered_set<std::string>({STMT_ATTR});
}

std::shared_ptr<EntityArgument> IfCreator::create(std::string name) {
    return std::make_shared<IfStmtEntity>(name, STMT_ATTR);
}

std::shared_ptr<EntityArgument> IfCreator::create(std::string name, std::string attrRef) {
    return std::make_shared<IfStmtEntity>(name, isAttrRefValid(validAttrRefs, attrRef));
}
