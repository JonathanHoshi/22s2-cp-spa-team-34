// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once
#include "ExpressionNode.h"

class ConstantNode : public ExpressionNode {
protected:
    int value;

public:
    explicit ConstantNode(int value);
    void accept(ExtractorVisitor& e) override;

    // getter
    int getValue() const;

    // equality
    bool operator==(const ExpressionNode& rhs) const override;
    bool checkPartial(const ExpressionNode& rhs) const override;
};
