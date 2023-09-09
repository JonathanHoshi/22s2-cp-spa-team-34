// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once
#include <string>
#include <unordered_set>
#include "di/IService.h"

class IConstAdder : public virtual IService {
public:
    ~IConstAdder() override = default;

    virtual void addConst(const int& constVal) = 0;
    virtual void addConsts(const std::unordered_set<int>& constSet) = 0;
};
