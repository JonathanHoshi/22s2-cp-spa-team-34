// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "WithClauseCreator.h"

WithClauseCreator::WithClauseCreator() : ClauseCreator() {}

std::shared_ptr<Clause> WithClauseCreator::create(std::shared_ptr<Argument> firstArg,
    std::shared_ptr<Argument> secondArg) {
    return std::make_shared<Clause>(
        std::make_shared<WithStrategy>(), firstArg, secondArg);
}
