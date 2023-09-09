// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once
#include <string>
#include <unordered_set>
#include "di/IService.h"

class IProcGetter : public virtual IService {
public:
    ~IProcGetter() override = default;

    virtual std::unordered_set<std::string> getProcs() = 0;
    virtual bool isProc(const std::string& procStr) = 0;
    virtual size_t getSize() = 0;
};
