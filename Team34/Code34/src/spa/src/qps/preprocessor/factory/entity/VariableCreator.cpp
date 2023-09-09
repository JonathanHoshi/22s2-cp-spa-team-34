// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.
#include <unordered_set>
#include "VariableCreator.h"
#include "qps/argument/entity/VariableEntity.h"

VariableCreator::VariableCreator() : EntityCreator() {
    validAttrRefs = std::unordered_set<std::string>({VARNAME_ATTR});
}

std::shared_ptr<EntityArgument> VariableCreator::create(std::string name) {
    return std::make_shared<VariableEntity>(name, "varName");
}

std::shared_ptr<EntityArgument> VariableCreator::create(std::string name, std::string attrRef) {
    return std::make_shared<VariableEntity>(name, isAttrRefValid(validAttrRefs, attrRef));
}
