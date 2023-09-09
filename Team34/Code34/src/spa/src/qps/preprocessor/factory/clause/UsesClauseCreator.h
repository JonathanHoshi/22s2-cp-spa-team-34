// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once
#include <memory>
#include "ClauseCreator.h"
#include "qps/argument/input/StringInput.h"
#include "qps/clause/strategy/relation/UsesStrategy.h"

class UsesClauseCreator : public ClauseCreator {
public:
    std::shared_ptr<Clause> create(std::shared_ptr<Argument> firstArg,
        std::shared_ptr<Argument> secondArg) override;
};
