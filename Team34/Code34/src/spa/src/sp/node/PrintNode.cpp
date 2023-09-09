// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "PrintNode.h"
#include "sp/extractor/ExtractorVisitor.h"

PrintNode::PrintNode(int stmtNo) : StmtNode(stmtNo) {}

void PrintNode::accept(ExtractorVisitor& e) {
    e.extract(*this);
}

// getter
VariableNode* PrintNode::getVariable() {
    return this->printVar.get();
}

// setter
void PrintNode::setVariable(std::shared_ptr<VariableNode> node) {
    this->printVar = node;
}


bool PrintNode::operator==(const StmtNode& rhs) const {
    if (typeid(*this) != typeid(rhs)) {
        return false;
    }
    const PrintNode* print = dynamic_cast<const PrintNode*>(&rhs);
    return *(this->printVar) == *(print->printVar);
}
