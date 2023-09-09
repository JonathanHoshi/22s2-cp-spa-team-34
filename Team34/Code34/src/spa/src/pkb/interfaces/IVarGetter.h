// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once

#include <string>
#include <unordered_set>
#include "di/IService.h"

class IVarGetter : public virtual IService {
public:
    ~IVarGetter() override = default;

    virtual std::unordered_set<std::string> getVars() = 0;
    virtual bool isVar(const std::string& varStr) = 0;
    virtual size_t getSize() = 0;
};
