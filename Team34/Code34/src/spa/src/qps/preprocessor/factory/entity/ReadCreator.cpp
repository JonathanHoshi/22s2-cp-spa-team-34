// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.
#include <unordered_set>
#include "ReadCreator.h"

ReadCreator::ReadCreator() : EntityCreator() {
    validAttrRefs = std::unordered_set<std::string>({STMT_ATTR, VARNAME_ATTR});
}

std::shared_ptr<EntityArgument> ReadCreator::create(std::string name) {
    return std::make_shared<ReadStmtEntity>(name, STMT_ATTR);
}

std::shared_ptr<EntityArgument> ReadCreator::create(std::string name, std::string attrRef) {
    return std::make_shared<ReadStmtEntity>(name, isAttrRefValid(validAttrRefs, attrRef));
}
