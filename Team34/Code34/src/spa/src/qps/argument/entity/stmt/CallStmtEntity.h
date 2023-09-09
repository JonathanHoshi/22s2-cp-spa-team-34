// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once

#include <string>
#include <unordered_set>
#include "qps/argument/entity/stmt/StmtEntity.h"

class CallStmtEntity : public StmtEntity {
public:
    inline static const std::string TYPE_NAME = "call";

    CallStmtEntity(std::string name, std::string attrRef);
    CallStmtEntity(IStmtGetter* pkbInterface, std::string name, std::string attrRef);
    static bool checkInstance(const Argument* ptr);

    std::unordered_set<std::string> getPKBValueList() override;
    std::string getAttrFromPKB(std::string id) override;
    std::string getType() override;
};
