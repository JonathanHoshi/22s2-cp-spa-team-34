// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once
#include <string>
#include "ExpressionNode.h"

class VariableNode : public ExpressionNode {
protected:
    std::string name;

public:
    explicit VariableNode(std::string name);
    void accept(ExtractorVisitor& e) override;

    // getter
    std::string getName() const;

    // equality
    bool operator==(const ExpressionNode& rhs) const override;
    bool checkPartial(const ExpressionNode& rhs) const override;
};
