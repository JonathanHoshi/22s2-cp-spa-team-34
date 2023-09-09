// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "ProcedureNode.h"
#include "sp/extractor/ExtractorVisitor.h"

ProcedureNode::ProcedureNode(std::string name) {
    this->procedureName = name;
}

void ProcedureNode::accept(ExtractorVisitor& e) {
    e.extract(*this);
}

// getter
StmtLstNode* ProcedureNode::getStmtList() {
    return this->stmtList.get();
}

std::string ProcedureNode::getProcedureName() {
    return this->procedureName;
}

// setter
void ProcedureNode::setStmtList(std::shared_ptr<StmtLstNode> stmtList) {
    this->stmtList = stmtList;
}

bool ProcedureNode::operator==(const EntityNode& rhs) const {
    if (typeid(*this) != typeid(rhs)) {
        return false;
    }
    const ProcedureNode* procedure = dynamic_cast<const ProcedureNode*>(&rhs);
    return (*(this->stmtList) == *(procedure->stmtList)) &&
        (this->procedureName == procedure->procedureName);
}
