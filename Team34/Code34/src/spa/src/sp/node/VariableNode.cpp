// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "VariableNode.h"
#include "sp/extractor/ExtractorVisitor.h"

VariableNode::VariableNode(std::string name) : ExpressionNode() {
    this->name = name;
}

void VariableNode::accept(ExtractorVisitor& e) {
    e.extract(*this);
}

// getter
std::string VariableNode::getName() const {
    return this->name;
}

bool VariableNode::operator==(const ExpressionNode& rhs) const {
    if (typeid(*this) != typeid(rhs)) {
        return false;
    }
    const VariableNode* constant = dynamic_cast<const VariableNode*>(&rhs);
    return constant->name == this->name;
}

bool VariableNode::checkPartial(const ExpressionNode& rhs) const {
    return *this == rhs;
}
