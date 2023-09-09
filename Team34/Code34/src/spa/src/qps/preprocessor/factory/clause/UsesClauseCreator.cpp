// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "UsesClauseCreator.h"

std::shared_ptr<Clause> UsesClauseCreator::create(std::shared_ptr<Argument> firstArg,
    std::shared_ptr<Argument> secondArg) {
    bool isStringOrProd = StringInput::checkInstance(firstArg.get())
        || ProcedureEntity::checkInstance(firstArg.get());
    return std::make_shared<Clause>(
        std::make_shared<UsesStrategy>(isStringOrProd), firstArg, secondArg);
}
