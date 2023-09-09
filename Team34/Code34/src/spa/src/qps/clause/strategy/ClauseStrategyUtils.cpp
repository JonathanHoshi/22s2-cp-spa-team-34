// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "ClauseStrategyUtils.h"

#include "pkb/interfaces/IProcGetter.h"
#include "pkb/interfaces/IStmtGetter.h"
#include "pkb/interfaces/IVarGetter.h"

void ClauseStrategyUtils::
initializeWildcardRightArgVar(std::shared_ptr<Argument>& secondArg, DI& di) {
    if (WildcardEntity::checkInstance(secondArg.get())) {
        WildcardEntity* wildcardEntity = dynamic_cast<WildcardEntity*>(secondArg.get());

        wildcardEntity->assignEntityType(
            std::make_shared<VariableEntity>(&di.getService<IVarGetter>(), "", ""));
    }
}

void ClauseStrategyUtils::initializeWildcardBothArg(
    std::vector<std::shared_ptr<Argument>>& argumentList, bool isProcedure, DI& di) {
    // check first 2 arguments
    for (int i = 0; i < 2; i++) {
        std::shared_ptr<Argument> curArg = argumentList[i];

        if (!WildcardEntity::checkInstance(curArg.get())) {
            continue;
        }

        WildcardEntity* wildcardEntity = dynamic_cast<WildcardEntity*>(curArg.get());

        if (isProcedure) {
            wildcardEntity->assignEntityType(
                std::make_shared<ProcedureEntity>(&di.getService<IProcGetter>(), "", ""));
        } else {
            wildcardEntity->assignEntityType(
                std::make_shared<StmtStmtEntity>(&di.getService<IStmtGetter>(), "", ""));
        }
    }
}
