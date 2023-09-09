// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include <memory>
#include "AffectsClauseCreator.h"

AffectsClauseCreator::AffectsClauseCreator(bool isTransitive):
        TransitiveClauseCreator(isTransitive) {}

std::shared_ptr<Clause> AffectsClauseCreator::create(std::shared_ptr<Argument> firstArg,
                                                     std::shared_ptr<Argument> secondArg) {
    return std::make_shared<Clause>(
            std::make_shared<AffectsStrategy>(this->isTransitive), firstArg, secondArg);
}
