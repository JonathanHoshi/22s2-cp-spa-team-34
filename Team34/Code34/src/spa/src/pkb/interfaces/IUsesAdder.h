// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once

#include <string>
#include "di/IService.h"

class IUsesAdder : public virtual IService {
public:
    ~IUsesAdder() override = default;
    // Adds stmt-uses-var relation
    virtual void addVarS(const int& stmtNum, const std::string& varName) = 0;
    // Adds proc-uses-var relation
    virtual void addVarP(const std::string& procName, const std::string& varName) = 0;
};
