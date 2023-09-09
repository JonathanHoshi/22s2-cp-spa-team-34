// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once
#include <memory>
#include "TransitiveClauseCreator.h"
#include "qps/clause/strategy/relation/FollowsStrategy.h"

class FollowsClauseCreator : public TransitiveClauseCreator {
public:
    explicit FollowsClauseCreator(bool isTransitive);
    std::shared_ptr<Clause> create(std::shared_ptr<Argument> firstArg,
        std::shared_ptr<Argument> secondArg) override;
};
