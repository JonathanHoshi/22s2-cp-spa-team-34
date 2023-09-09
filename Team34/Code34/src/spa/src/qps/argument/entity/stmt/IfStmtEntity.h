// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once

#include <string>
#include <unordered_set>
#include "qps/argument/entity/stmt/StmtEntity.h"
#include "qps/argument/validator/PatternSynonym.h"

class IfStmtEntity : public StmtEntity, public PatternSynonym {
public:
    inline static const std::string TYPE_NAME = "if";

    IfStmtEntity(std::string name, std::string attrRef);
    IfStmtEntity(IStmtGetter* pkbInterface, std::string name, std::string attrRef);
    static bool checkInstance(const Argument* ptr);

    std::unordered_set<std::string> getPKBValueList() override;
    std::string getType() override;
};
