// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.
#pragma once

#include <string>
#include <unordered_set>
#include "di/IService.h"

class IIfPatternAdder : public virtual IService {
public:
    ~IIfPatternAdder() override = default;

    virtual void addIfPattern(const int& stmtNum,
        const std::unordered_set<std::string>& val) = 0;  // Adds if pattern
};
