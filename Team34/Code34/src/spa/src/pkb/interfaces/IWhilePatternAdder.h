// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.
#pragma once

#include <string>
#include <unordered_set>
#include "di/IService.h"

class IWhilePatternAdder : public virtual IService {
public:
    ~IWhilePatternAdder() override = default;

    virtual void addWhilePattern(const int& stmtNum,
        const std::unordered_set<std::string>& val) = 0;  // Adds while pattern
};
