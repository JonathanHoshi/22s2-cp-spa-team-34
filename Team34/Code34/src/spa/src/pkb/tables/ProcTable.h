// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once

#include <unordered_set>
#include <string>
#include "pkb/interfaces/IProcAdder.h"
#include "pkb/interfaces/IProcGetter.h"
#include "pkb/base/BaseSet.h"

class ProcTable : public IProcAdder, public IProcGetter {
private:
    BaseSet<std::string> procList;
public:
    std::unordered_set<std::string> getProcs() override;
    void addProc(const std::string& procStr) override;
    void addProcs(const std::unordered_set<std::string>& procSet) override;
    bool isProc(const std::string& procStr) override;
    size_t getSize() override;
};
