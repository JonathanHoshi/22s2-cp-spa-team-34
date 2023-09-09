// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once

#include <unordered_set>
#include <string>
#include "pkb/interfaces/IVarAdder.h"
#include "pkb/interfaces/IVarGetter.h"
#include "pkb/base/BaseSet.h"

class VarTable : public IVarAdder, public IVarGetter {
private:
    BaseSet<std::string> varList;

public:
    std::unordered_set<std::string> getVars() override;
    void addVar(const std::string& varStr) override;
    void addVars(const std::unordered_set<std::string>& varSet) override;
    bool isVar(const std::string& varStr) override;
    size_t getSize() override;
};
