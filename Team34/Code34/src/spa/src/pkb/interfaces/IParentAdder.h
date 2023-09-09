// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once
#include <string>
#include "di/IService.h"

class IParentAdder : public virtual IService {
public:
    ~IParentAdder() override = default;

    // Adds parent-child relation
    virtual void addRelation(const int& keyStmt, const int& valStmt) = 0;
    // Adds parent-child T relation
    virtual void addRelationT(const int& keyStmt, const int& valStmt) = 0;
};
