// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.
#include "NextClauseCreator.h"

NextClauseCreator::NextClauseCreator(bool isTransitive) :
    TransitiveClauseCreator(isTransitive) {}

std::shared_ptr<Clause> NextClauseCreator::create(std::shared_ptr<Argument> firstArg,
    std::shared_ptr<Argument> secondArg) {
    return std::make_shared<Clause>(
        std::make_shared<NextStrategy>(this->isTransitive), firstArg, secondArg);
}
