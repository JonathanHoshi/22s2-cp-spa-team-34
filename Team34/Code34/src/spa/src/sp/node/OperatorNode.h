// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once
#include <memory>
#include <string>
#include <vector>
#include "ExpressionNode.h"

class OperatorNode : public ExpressionNode {
protected:
    std::vector<std::shared_ptr<ExpressionNode>> neighbors;
    std::string value;

public:
    explicit OperatorNode(std::string value);
    void accept(ExtractorVisitor& e) override;

    // getter
    std::string getValue() const;
    ExpressionNode* getNeighbor(int idx) const;
    int getNeighborCount() const;

    // setter
    void addRHS(std::shared_ptr<ExpressionNode> node);
    void addLHS(std::shared_ptr<ExpressionNode> node);

    // equality
    bool operator==(const ExpressionNode& rhs) const override;
    bool checkPartial(const ExpressionNode& rhs) const override;
};
