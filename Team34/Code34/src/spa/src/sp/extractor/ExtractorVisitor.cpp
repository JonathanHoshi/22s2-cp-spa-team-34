// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "ExtractorVisitor.h"
#include "sp/node/RootNode.h"

void ExtractorVisitor::begin(RootNode& node) {
    node.accept(*this);
}

void ExtractorVisitor::extract(StmtLstNode& node) {
    for (int i = 0; i < node.getStmtCount(); i++) {
        node.getStmt(i)->accept(*this);
    }
}

void ExtractorVisitor::extract(RootNode& node) {
    for (int i = 0; i < node.getProcedureCount(); i++) {
        node.getProcedure(i)->accept(*this);
    }
}

void ExtractorVisitor::extract(ProcedureNode& node) {
    node.getStmtList()->accept(*this);
}
