// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "WhileNode.h"
#include "sp/extractor/ExtractorVisitor.h"

WhileNode::WhileNode(int stmtNo) : StmtNode(stmtNo) {}

void WhileNode::accept(ExtractorVisitor& e) {
    e.extract(*this);
}

// getter
ExpressionNode* WhileNode::getCondition() {
    return this->condition.get();
}

StmtLstNode* WhileNode::getStmtLst() {
    return this->stmtList.get();
}

// setter
void WhileNode::setCondition(std::shared_ptr<ExpressionNode> node) {
    this->condition = node;
}

void WhileNode::setStmtLst(std::shared_ptr<StmtLstNode> node) {
    this->stmtList = node;
}

bool WhileNode::operator==(const StmtNode& rhs) const {
    if (typeid(*this) != typeid(rhs)) {
        return false;
    }
    const WhileNode* whileNode = dynamic_cast<const WhileNode*>(&rhs);
    return (*(this->condition) == *(whileNode->condition)) &&
        (*(this->stmtList) == *(whileNode->stmtList));
}
