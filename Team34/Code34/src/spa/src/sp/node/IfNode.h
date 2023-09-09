// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once
#include <memory>
#include "StmtNode.h"
#include "ExpressionNode.h"
#include "StmtLstNode.h"

class IfNode : public StmtNode {
protected:
    std::shared_ptr<ExpressionNode> condition;
    std::shared_ptr<StmtLstNode> thenStmtList;
    std::shared_ptr<StmtLstNode> elseStmtList;

public:
    explicit IfNode(int stmtNo);
    void accept(ExtractorVisitor& e) override;

    // getter
    ExpressionNode* getCondition();
    StmtLstNode* getThen();
    StmtLstNode* getElse();

    // setter
    void setCondition(std::shared_ptr<ExpressionNode> node);
    void setThen(std::shared_ptr<StmtLstNode> node);
    void setElse(std::shared_ptr<StmtLstNode> node);

    bool operator==(const StmtNode& rhs) const override;
};
