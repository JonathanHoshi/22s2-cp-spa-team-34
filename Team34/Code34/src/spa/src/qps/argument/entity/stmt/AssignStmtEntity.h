// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once

#include <string>
#include <unordered_set>
#include "qps/argument/entity/stmt/StmtEntity.h"
#include "qps/argument/validator/PatternSynonym.h"
#include "qps/argument/validator/AffectsArg.h"


class AssignStmtEntity : public StmtEntity, public PatternSynonym {
public:
    inline static const std::string TYPE_NAME = "assign";

    AssignStmtEntity(std::string name, std::string attrRef);
    AssignStmtEntity(IStmtGetter* pkbInterface, std::string name, std::string attrRef);
    static bool checkInstance(const Argument* ptr);
    static bool checkType(const EntityArgument* ptr);

    std::unordered_set<std::string> getPKBValueList() override;
    std::string getType() override;
};
