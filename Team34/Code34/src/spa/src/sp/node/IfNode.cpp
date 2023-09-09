// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "IfNode.h"
#include "sp/extractor/ExtractorVisitor.h"

IfNode::IfNode(int stmtNo) : StmtNode(stmtNo) {}

void IfNode::accept(ExtractorVisitor& e) {
    e.extract(*this);
}

// getter
ExpressionNode* IfNode::getCondition() {
    return condition.get();
}

StmtLstNode* IfNode::getThen() {
    return this->thenStmtList.get();
}

StmtLstNode* IfNode::getElse() {
    return this->elseStmtList.get();
}

// setter
void IfNode::setCondition(std::shared_ptr<ExpressionNode> node) {
    this->condition = node;
}

void IfNode::setThen(std::shared_ptr<StmtLstNode> node) {
    this->thenStmtList = node;
}

void IfNode::setElse(std::shared_ptr<StmtLstNode> node) {
    this->elseStmtList = node;
}

bool IfNode::operator==(const StmtNode& rhs) const {
    if (typeid(*this) != typeid(rhs)) {
        return false;
    }
    const IfNode* ifNode = dynamic_cast<const IfNode*>(&rhs);
    return (*(this->condition) == *(ifNode->condition)) &&
        (*(this->thenStmtList) == *(ifNode->thenStmtList)) &&
        (*(this->elseStmtList) == *(ifNode->elseStmtList));
}
