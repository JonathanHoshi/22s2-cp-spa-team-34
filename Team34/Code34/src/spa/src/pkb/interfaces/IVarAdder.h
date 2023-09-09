// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once

#include <string>
#include <unordered_set>
#include "di/IService.h"

class IVarAdder : public virtual IService {
public:
    ~IVarAdder() override = default;

    virtual void addVar(const std::string& varStr) = 0;
    virtual void addVars(const std::unordered_set<std::string>& varSet) = 0;
};
