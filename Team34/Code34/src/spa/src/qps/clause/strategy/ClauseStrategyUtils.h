// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once

#include <memory>
#include <string>
#include <vector>

#include "di/DI.h"
#include "qps/argument/Argument.h"
#include "qps/argument/entity/WildcardEntity.h"
#include "qps/argument/entity/VariableEntity.h"
#include "qps/argument/entity/stmt/StmtStmtEntity.h"
#include "qps/argument/entity/ProcedureEntity.h"



class ClauseStrategyUtils {
public:
    static void initializeWildcardRightArgVar(std::shared_ptr<Argument>& secondArg, DI& di);
    static void initializeWildcardBothArg(std::vector<std::shared_ptr<Argument>>& argumentList,
        bool isProcedure, DI& di);

private:
    ClauseStrategyUtils();
};
