// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once
#include <string>
#include "di/IService.h"

class IFollowsAdder : public virtual IService {
public:
    ~IFollowsAdder() override = default;

    // Adds before-follows-after relation
    virtual void addRelation(const int& keyStmt, const int& valStmt) = 0;
    // Adds before-followsT-after relation
    virtual void addRelationT(const int& keyStmt, const int& valStmt) = 0;
};
