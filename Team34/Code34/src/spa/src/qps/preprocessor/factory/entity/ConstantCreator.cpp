// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.
#include <unordered_set>
#include "ConstantCreator.h"
#include "qps/argument/entity/ConstantEntity.h"

ConstantCreator::ConstantCreator() {
    validAttrRefs = std::unordered_set<std::string>({VALUE_ATTR});
}

std::shared_ptr<EntityArgument> ConstantCreator::create(std::string name) {
    return std::make_shared<ConstantEntity>(name, VALUE_ATTR);
}

std::shared_ptr<EntityArgument> ConstantCreator::create(std::string name, std::string attrRef) {
    return std::make_shared<ConstantEntity>(name, isAttrRefValid(validAttrRefs, attrRef));
}
