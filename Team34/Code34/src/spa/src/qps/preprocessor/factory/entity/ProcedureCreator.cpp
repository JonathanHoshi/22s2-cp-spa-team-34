// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include <unordered_set>
#include "ProcedureCreator.h"
#include "qps/argument/entity/ProcedureEntity.h"

ProcedureCreator::ProcedureCreator() {
    validAttrRefs = std::unordered_set<std::string>({PROCNAME_ATTR});
}

std::shared_ptr<EntityArgument> ProcedureCreator::create(std::string name) {
    return std::make_shared<ProcedureEntity>(name, PROCNAME_ATTR);
}

std::shared_ptr<EntityArgument> ProcedureCreator::create(std::string name, std::string attrRef) {
    return std::make_shared<ProcedureEntity>(name, isAttrRefValid(validAttrRefs, attrRef));
}
