// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "ReadNode.h"
#include "sp/extractor/ExtractorVisitor.h"

ReadNode::ReadNode(int stmtNo) : StmtNode(stmtNo) {}

void ReadNode::accept(ExtractorVisitor& e) {
    e.extract(*this);
}

// getter
VariableNode* ReadNode::getVariable() {
    return this->readVar.get();
}

// setter
void ReadNode::setVariable(std::shared_ptr<VariableNode> node) {
    this->readVar = node;
}

bool ReadNode::operator==(const StmtNode& rhs) const {
    if (typeid(*this) != typeid(rhs)) {
        return false;
    }
    const ReadNode* read = dynamic_cast<const ReadNode*>(&rhs);
    return *(this->readVar) == *(read->readVar);
}
