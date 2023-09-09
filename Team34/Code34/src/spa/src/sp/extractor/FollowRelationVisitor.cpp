// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "FollowRelationVisitor.h"
#include "common/CollectionUtils.h"
#include "sp/node/IfNode.h"
#include "sp/node/WhileNode.h"
#include "common/exceptions/TransverseError.h"

FollowRelationVisitor::FollowRelationVisitor(IFollowsAdder& adder) {
    this->adder = &adder;
}

void FollowRelationVisitor::extract(VariableNode& node) {
    throw TransverseError{"FollowsExtractor should not be looking at a variable node"};
}

void FollowRelationVisitor::extract(ConstantNode& node) {
    throw TransverseError{"FollowsExtractor should not be looking at a constant node"};
}

void FollowRelationVisitor::extract(OperatorNode& node) {
    throw TransverseError{"FollowsExtractor should not be looking at a operator node"};
}

// Statement nodes that should not do anything when visited
void FollowRelationVisitor::extract(ReadNode& node) {}
void FollowRelationVisitor::extract(PrintNode& node) {}
void FollowRelationVisitor::extract(CallNode& node) {}
void FollowRelationVisitor::extract(AssignNode& node) {}

void FollowRelationVisitor::extract(IfNode& node) {
    node.getThen()->accept(*this);
    node.getElse()->accept(*this);
}

void FollowRelationVisitor::extract(WhileNode& node) {
    node.getStmtLst()->accept(*this);
}

void FollowRelationVisitor::extract(StmtLstNode& node) {
    ExtractorVisitor::extract(node);
    std::unordered_set<int> set;
    for (int i = node.getStmtCount() - 1; i > 0; i--) {
        int preStmtNo = node.getStmt(i - 1)->getStmtNumber();
        int postStmtNo = node.getStmt(i)->getStmtNumber();
        followsMap.insert({preStmtNo, postStmtNo});
        set.insert(postStmtNo);
        CollectionUtils::insert(followsTMap, preStmtNo, set);
    }
}

void FollowRelationVisitor::transfer() {
    for (auto& [preStmt, postStmt] : followsMap) {
        adder->addRelation(preStmt, postStmt);
    }

    for (auto& [preStmt, stmtSet] : followsTMap) {
        for (const int& postStmt : stmtSet) {
            adder->addRelationT(preStmt, postStmt);
        }
    }
}
