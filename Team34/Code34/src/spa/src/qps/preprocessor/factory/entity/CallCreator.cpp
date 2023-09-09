// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.
#include <unordered_set>
#include "CallCreator.h"

CallCreator::CallCreator() : EntityCreator() {
    validAttrRefs = std::unordered_set<std::string>({STMT_ATTR, PROCNAME_ATTR});
}

std::shared_ptr<EntityArgument> CallCreator::create(std::string name) {
    return std::make_shared<CallStmtEntity>(name, STMT_ATTR);
}

std::shared_ptr<EntityArgument> CallCreator::create(std::string name, std::string attrRef) {
    return std::make_shared<CallStmtEntity>(name, isAttrRefValid(validAttrRefs, attrRef));
}
