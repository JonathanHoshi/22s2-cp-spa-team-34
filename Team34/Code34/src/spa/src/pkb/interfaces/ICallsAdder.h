// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once

#include <string>
#include "di/IService.h"

class ICallsAdder : public virtual IService {
public:
    ~ICallsAdder() override = default;

    virtual void addCalls(const std::string& callerProc,
        const std::string& calleeProc) = 0;  // Adds call relation
    virtual void addCallsT(const std::string& callerProc,
        const std::string& calleeProc) = 0;  // Adds callsT relation
};
