// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "ConstantNode.h"
#include "sp/extractor/ExtractorVisitor.h"

ConstantNode::ConstantNode(int value) : ExpressionNode() {
    this->value = value;
}

int ConstantNode::getValue() const {
    return this->value;
}

void ConstantNode::accept(ExtractorVisitor& e) {
    e.extract(*this);
}

bool ConstantNode::operator==(const ExpressionNode& rhs) const {
    if (typeid(*this) != typeid(rhs)) {
        return false;
    }
    const ConstantNode* constant = dynamic_cast<const ConstantNode*>(&rhs);
    return constant->value == this->value;
}

bool ConstantNode::checkPartial(const ExpressionNode& rhs) const {
    return *this == rhs;
}
