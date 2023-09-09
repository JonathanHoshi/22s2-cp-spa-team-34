// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once
#include <memory>
#include "StmtNode.h"
#include "ExpressionNode.h"
#include "VariableNode.h"

class AssignNode : public StmtNode {
protected:
    std::shared_ptr<VariableNode> variable;
    std::shared_ptr<ExpressionNode> expression;

public:
    explicit AssignNode(int stmtNo);
    void accept(ExtractorVisitor& e) override;
    // getter
    VariableNode* getVariable();
    ExpressionNode* getExpression();
    std::shared_ptr<ExpressionNode> getExpressionOwnership();
    // setter
    void setVariable(std::shared_ptr<VariableNode> variable);
    void setExpression(std::shared_ptr<ExpressionNode> expression);

    bool operator==(const StmtNode& rhs) const override;
};
