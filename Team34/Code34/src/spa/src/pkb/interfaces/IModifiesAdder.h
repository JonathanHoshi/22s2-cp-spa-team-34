// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once
#include <string>
#include "di/IService.h"

class IModifiesAdder : public virtual IService {
public:
    ~IModifiesAdder() override = default;
    // Adds stmt-modifies-var relation
    virtual void addVarS(const int& stmtNum, const std::string& varName) = 0;
    // Adds proc-modifies-var relation
    virtual void addVarP(const std::string& procName, const std::string& varName) = 0;
};
