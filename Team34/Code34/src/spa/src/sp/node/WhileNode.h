// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once
#include <memory>
#include "StmtNode.h"
#include "ExpressionNode.h"
#include "StmtLstNode.h"

class WhileNode : public StmtNode {
protected:
    std::shared_ptr<ExpressionNode> condition;
    std::shared_ptr<StmtLstNode> stmtList;

public:
    explicit WhileNode(int stmtNo);
    void accept(ExtractorVisitor& e) override;

    // getter
    ExpressionNode* getCondition();
    StmtLstNode* getStmtLst();

    // setter
    void setCondition(std::shared_ptr<ExpressionNode> node);
    void setStmtLst(std::shared_ptr<StmtLstNode> node);

    bool operator==(const StmtNode& rhs) const override;
};
