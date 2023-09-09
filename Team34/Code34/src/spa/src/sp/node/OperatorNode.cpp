// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "OperatorNode.h"
#include "sp/extractor/ExtractorVisitor.h"

OperatorNode::OperatorNode(std::string value) : ExpressionNode() {
    this->value = value;
}

void OperatorNode::accept(ExtractorVisitor& e) {
    e.extract(*this);
}

// getter
std::string OperatorNode::getValue() const {
    return this->value;
}
ExpressionNode* OperatorNode::getNeighbor(int idx) const {
    return this->neighbors.at(idx).get();
}
int OperatorNode::getNeighborCount() const {
    return this->neighbors.size();
}

// setter
void OperatorNode::addRHS(std::shared_ptr<ExpressionNode> node) {
    this->neighbors.push_back(node);
}

void OperatorNode::addLHS(std::shared_ptr<ExpressionNode> node) {
    this->neighbors.insert(this->neighbors.begin(), node);
}

bool OperatorNode::operator==(const ExpressionNode& rhs) const {
    if (typeid(*this) != typeid(rhs)) {
        return false;
    }
    const OperatorNode* opt = dynamic_cast<const OperatorNode*>(&rhs);

    if (this->value != opt->value || this->getNeighborCount() != opt->getNeighborCount())
        return false;

    for (int i = 0; i < this->getNeighborCount(); i++) {
        bool eq = *(this->getNeighbor(i)) == *(opt->getNeighbor(i));
        if (!eq)
            return false;
    }
    return true;
}

bool OperatorNode::checkPartial(const ExpressionNode& rhs) const {
    if (*this == rhs) {
        return true;
    }
    for (int i = 0; i < this->getNeighborCount(); i++) {
        if (this->getNeighbor(i)->checkPartial(rhs))
            return true;
    }
    return false;
}
