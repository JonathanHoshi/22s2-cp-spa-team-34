// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once
#include "EntityNode.h"

class ExpressionNode : public EntityNode {
protected:
    ExpressionNode() {}

public:
    virtual bool checkPartial(const ExpressionNode& rhs) const = 0;
    virtual bool operator==(const ExpressionNode& rhs) const = 0;
};
