// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once

#include <string>
#include "StmtEntity.h"

class StmtStmtEntity: public StmtEntity {
public:
    StmtStmtEntity(std::string name, std::string attrRef);
    StmtStmtEntity(IStmtGetter* pkbInterface, std::string name, std::string attrRef);
    static bool checkInstance(const Argument* ptr);
    static bool checkType(const EntityArgument* ptr);
};
