// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "CFGExtractorVisitor.h"
#include "common/CollectionUtils.h"
#include "sp/node/ReadNode.h"
#include "sp/node/PrintNode.h"
#include "sp/node/AssignNode.h"
#include "sp/node/IfNode.h"
#include "sp/node/WhileNode.h"
#include "sp/node/CallNode.h"
#include "sp/node/ProcedureNode.h"

CFGExtractorVisitor::CFGExtractorVisitor(INextAdder& adder) {
    this->adder = &adder;
}

void CFGExtractorVisitor::insertAllStmts(int stmtNo) {
    for (auto previousStmt : previousStmts) {
        CollectionUtils::insert(cfg, previousStmt, stmtNo);
    }
    previousStmts.clear();
    previousStmts.insert(stmtNo);
}

void CFGExtractorVisitor::extract(ProcedureNode& node) {
    previousStmts.clear();
    ExtractorVisitor::extract(node);
}

void CFGExtractorVisitor::extract(VariableNode& node) {
    throw TransverseError{"CFG should not be looking at a variable node"};
}

void CFGExtractorVisitor::extract(ConstantNode& node) {
    throw TransverseError{"CFG should not be looking at a constant node"};
}

void CFGExtractorVisitor::extract(OperatorNode& node) {
    throw TransverseError{"CFG should not be looking at a operator node"};
}

void CFGExtractorVisitor::extract(ReadNode& node) {
    insertAllStmts(node.getStmtNumber());
}

void CFGExtractorVisitor::extract(PrintNode& node) {
    insertAllStmts(node.getStmtNumber());
}

void CFGExtractorVisitor::extract(CallNode& node) {
    insertAllStmts(node.getStmtNumber());
}

void CFGExtractorVisitor::extract(AssignNode& node) {
    insertAllStmts(node.getStmtNumber());
}

void CFGExtractorVisitor::extract(IfNode& node) {
    std::unordered_set<int> set;
    insertAllStmts(node.getStmtNumber());
    node.getThen()->accept(*this);
    CollectionUtils::merge(set, previousStmts);
    previousStmts = {node.getStmtNumber()};
    node.getElse()->accept(*this);
    CollectionUtils::merge(previousStmts, set);
}

void CFGExtractorVisitor::extract(WhileNode& node) {
    insertAllStmts(node.getStmtNumber());
    node.getStmtLst()->accept(*this);
    insertAllStmts(node.getStmtNumber());
}


void CFGExtractorVisitor::transfer() {
    for (auto& [stmt, set] : cfg) {
        for (auto& nextStmt : set) {
            this->adder->addNext(stmt, nextStmt);
        }
    }
}
