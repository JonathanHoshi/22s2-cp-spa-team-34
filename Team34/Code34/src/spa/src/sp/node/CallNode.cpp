// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "CallNode.h"
#include "sp/extractor/ExtractorVisitor.h"

CallNode::CallNode(int stmtNo, std::string val)
    : StmtNode(stmtNo) {
    this->procedureCall = val;
}

std::string CallNode::getProcedureName() {
    return this->procedureCall;
}
void CallNode::accept(ExtractorVisitor& e) {
    e.extract(*this);
}

bool CallNode::operator==(const StmtNode& rhs) const {
    if (typeid(*this) != typeid(rhs)) {
        return false;
    }
    const CallNode* call = dynamic_cast<const CallNode*>(&rhs);
    return this->procedureCall == call->procedureCall;
}
