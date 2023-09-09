// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "CallsClauseCreator.h"

CallsClauseCreator::CallsClauseCreator(bool isTransitive) :
    TransitiveClauseCreator(isTransitive) {}

std::shared_ptr<Clause> CallsClauseCreator::
create(std::shared_ptr<Argument> firstArg, std::shared_ptr<Argument> secondArg) {
    return std::make_shared<Clause>(
        std::make_shared<CallsStrategy>(this->isTransitive), firstArg, secondArg);
}
