// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once
#include <unordered_set>
#include "di/IService.h"

class IConstGetter : public virtual IService {
public:
    ~IConstGetter() override = default;

    virtual std::unordered_set<int> getConsts() = 0;
    virtual bool isConst(const int& constVal) = 0;
    virtual size_t getSize() = 0;
};
