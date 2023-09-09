// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "ModifiesClauseCreator.h"

std::shared_ptr<Clause> ModifiesClauseCreator::create(std::shared_ptr<Argument> firstArg,
    std::shared_ptr<Argument> secondArg) {
    std::shared_ptr<ClauseStrategy> clauseStrategy =
        std::make_shared<ModifiesStrategy>(StringInput::checkInstance(firstArg.get())
            || ProcedureEntity::checkInstance(firstArg.get()));
    return std::make_shared<Clause>(clauseStrategy, firstArg, secondArg);
}
