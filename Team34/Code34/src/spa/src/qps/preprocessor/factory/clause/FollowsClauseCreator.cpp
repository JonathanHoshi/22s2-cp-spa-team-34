// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "FollowsClauseCreator.h"

FollowsClauseCreator::FollowsClauseCreator(bool isTransitive) :
    TransitiveClauseCreator(isTransitive) {}

std::shared_ptr<Clause> FollowsClauseCreator::
create(std::shared_ptr<Argument> firstArg, std::shared_ptr<Argument> secondArg) {
    return std::make_shared<Clause>(
        std::make_shared<FollowsStrategy>(this->isTransitive), firstArg, secondArg);
}
