// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once

#include <unordered_set>
#include "pkb/interfaces/IConstAdder.h"
#include "pkb/interfaces/IConstGetter.h"
#include "pkb/base/BaseSet.h"

class ConstTable : public IConstAdder, public IConstGetter {
private:
    BaseSet<int> constList;

public:
    std::unordered_set<int> getConsts() override;
    void addConst(const int& constVal) override;
    void addConsts(const std::unordered_set<int>& constSet) override;
    bool isConst(const int& constVal) override;
    size_t getSize() override;
};
