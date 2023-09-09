// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "ParentClauseCreator.h"

ParentClauseCreator::ParentClauseCreator(bool isTransitive) :
    TransitiveClauseCreator(isTransitive) {}

std::shared_ptr<Clause> ParentClauseCreator::create(std::shared_ptr<Argument> firstArg,
    std::shared_ptr<Argument> secondArg) {
    return std::make_shared<Clause>(
        std::make_shared<ParentStrategy>(this->isTransitive), firstArg, secondArg);
}
