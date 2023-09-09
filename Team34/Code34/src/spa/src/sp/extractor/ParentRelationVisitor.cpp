// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "ParentRelationVisitor.h"
#include "sp/node/IfNode.h"
#include "sp/node/WhileNode.h"
#include "common/exceptions/TransverseError.h"
#include "common/CollectionUtils.h"

ParentRelationVisitor::ParentRelationVisitor(IParentAdder& adder) {
    this->adder = &adder;
}

void ParentRelationVisitor::extract(VariableNode& node) {
    throw TransverseError{"ParentExtractor should not be looking at a variable node"};
}

void ParentRelationVisitor::extract(ConstantNode& node) {
    throw TransverseError{"ParentExtractor should not be looking at a constant node"};
}

void ParentRelationVisitor::extract(OperatorNode& node) {
    throw TransverseError{"ParentExtractor should not be looking at a operator node"};
}

// Statement nodes that dont have nested parent
void ParentRelationVisitor::extract(ReadNode& node) {}
void ParentRelationVisitor::extract(PrintNode& node) {}
void ParentRelationVisitor::extract(CallNode& node) {}
void ParentRelationVisitor::extract(AssignNode& node) {}

void ParentRelationVisitor::extract(IfNode& node) {
    node.getThen()->accept(*this);
    node.getElse()->accept(*this);
    mergeChildren(node.getStmtNumber(), *node.getThen());
    mergeChildren(node.getStmtNumber(), *node.getElse());
}

void ParentRelationVisitor::extract(WhileNode& node) {
    node.getStmtLst()->accept(*this);
    mergeChildren(node.getStmtNumber(), *node.getStmtLst());
}

void ParentRelationVisitor::mergeChildren(const int& parentStmtNumber, StmtLstNode& stmtList) {
    for (int i = 0; i < stmtList.getStmtCount(); i++) {
        int childStmtNumber = stmtList.getStmt(i)->getStmtNumber();
        CollectionUtils::insert(parentsMap, parentStmtNumber, childStmtNumber);
        CollectionUtils::insert(parentsTMap, parentStmtNumber, childStmtNumber);
        if (parentsTMap.count(childStmtNumber) > 0) {
            CollectionUtils::insert(parentsTMap,
                parentStmtNumber, parentsTMap.at(childStmtNumber));
        }
    }
}

void ParentRelationVisitor::transfer() {
    for (auto& [parentStmt, stmtSet] : parentsMap) {
        for (const int& childStmt : stmtSet) {
            adder->addRelation(parentStmt, childStmt);
        }
    }
    for (auto& [parentStmt, stmtSet] : parentsTMap) {
        for (const int& childStmt : stmtSet) {
            adder->addRelationT(parentStmt, childStmt);
        }
    }
}
