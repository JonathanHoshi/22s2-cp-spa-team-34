// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once

#include <memory>
#include "ClauseCreator.h"
#include "qps/clause/strategy/WithStrategy.h"

class WithClauseCreator : public ClauseCreator {
public:
    WithClauseCreator();
    std::shared_ptr<Clause> create(std::shared_ptr<Argument> firstArg,
        std::shared_ptr<Argument> secondArg) override;
};
