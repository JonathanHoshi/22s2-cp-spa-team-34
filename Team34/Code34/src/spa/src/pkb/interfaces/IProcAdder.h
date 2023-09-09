// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once

#include <string>
#include <unordered_set>
#include "di/IService.h"

class IProcAdder : public virtual IService {
public:
    ~IProcAdder() override = default;

    virtual void addProc(const std::string& procStr) = 0;
    virtual void addProcs(const std::unordered_set<std::string>& procSet) = 0;
};
