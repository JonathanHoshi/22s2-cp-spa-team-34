// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "StmtLstNode.h"
#include "sp/extractor/ExtractorVisitor.h"

StmtLstNode::StmtLstNode() {}

void StmtLstNode::accept(ExtractorVisitor& e) {
    e.extract(*this);
}

// getter
StmtNode* StmtLstNode::getStmt(int i) {
    return this->stmts.at(i).get();
}

int StmtLstNode::getStmtCount() {
    return this->stmts.size();
}

// setters
void StmtLstNode::addStmt(std::shared_ptr<StmtNode> stmt) {
    this->stmts.push_back(stmt);
}

bool StmtLstNode::operator==(const EntityNode& rhs) const {
    bool flag = true;

    if (typeid(*this) != typeid(rhs)) {
        return false;
    }
    const StmtLstNode* stmtLst = dynamic_cast<const StmtLstNode*>(&rhs);

    if (this->stmts.size() != stmtLst->stmts.size()) {
        return false;
    }

    for (int i = 0; i < stmts.size(); i++) {
        flag = flag && *(this->stmts.at(i)) == *(stmtLst->stmts.at(i));
    }

    return flag;
}
