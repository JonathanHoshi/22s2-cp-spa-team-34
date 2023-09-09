// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "AssignNode.h"
#include "sp/extractor/ExtractorVisitor.h"

AssignNode::AssignNode(int stmtNo) : StmtNode(stmtNo) {}

void AssignNode::accept(ExtractorVisitor& e) {
    e.extract(*this);
}

VariableNode* AssignNode::getVariable() {
    return this->variable.get();
}

ExpressionNode* AssignNode::getExpression() {
    return this->expression.get();
}

std::shared_ptr<ExpressionNode> AssignNode::getExpressionOwnership() {
    return this->expression;
}

// setter
void AssignNode::setVariable(std::shared_ptr<VariableNode> variable) {
    this->variable = variable;
}

void AssignNode::setExpression(std::shared_ptr<ExpressionNode> expression) {
    this->expression = expression;
}

bool AssignNode::operator==(const StmtNode& rhs) const {
    if (typeid(*this) != typeid(rhs)) {
        return false;
    }
    const AssignNode* assign = dynamic_cast<const AssignNode*>(&rhs);
    return (*(this->variable) == *(assign->variable)) &&
        (*(this->expression) == *(assign->expression));
}
