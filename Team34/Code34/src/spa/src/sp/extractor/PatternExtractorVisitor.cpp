// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "PatternExtractorVisitor.h"
#include "sp/node/IfNode.h"
#include "sp/node/WhileNode.h"
#include "sp/node/AssignNode.h"
#include "sp/node/VariableNode.h"
#include "sp/node/ConstantNode.h"
#include "sp/node/OperatorNode.h"
#include "common/CollectionUtils.h"

PatternExtractorVisitor::PatternExtractorVisitor(IAssignPatternAdder& assignAdder,
    IIfPatternAdder& ifAdder, IWhilePatternAdder& whileAdder) {
    this->assignAdder = &assignAdder;
    this->ifAdder = &ifAdder;
    this->whileAdder = &whileAdder;
}

void PatternExtractorVisitor::extract(VariableNode& node) {
    expressionVars.push(node.getName());
}

void PatternExtractorVisitor::extract(ConstantNode& node) {}

void PatternExtractorVisitor::extract(OperatorNode& node) {
    for (int i = 0; i < node.getNeighborCount(); i++) {
        node.getNeighbor(i)->accept(*this);
    }
}

// Statement nodes without pattern
void PatternExtractorVisitor::extract(ReadNode& node) {}
void PatternExtractorVisitor::extract(PrintNode& node) {}
void PatternExtractorVisitor::extract(CallNode& node) {}

void PatternExtractorVisitor::extract(IfNode& node) {
    std::unordered_set<std::string> ifSet;
    node.getCondition()->accept(*this);
    CollectionUtils::popStackIntoSet(expressionVars, ifSet);
    CollectionUtils::insert(ifPatternMap, node.getStmtNumber(), ifSet);
    node.getThen()->accept(*this);
    node.getElse()->accept(*this);
}

void PatternExtractorVisitor::extract(WhileNode& node) {
    std::unordered_set<std::string> whileSet;
    node.getCondition()->accept(*this);
    CollectionUtils::popStackIntoSet(expressionVars, whileSet);
    CollectionUtils::insert(whilePatternMap, node.getStmtNumber(), whileSet);
    node.getStmtLst()->accept(*this);
}

void PatternExtractorVisitor::extract(AssignNode& node) {
    int stmtNo = node.getStmtNumber();
    std::string var = node.getVariable()->getName();
    std::shared_ptr<ExpressionNode> pattern = node.getExpressionOwnership();
    assignPatternMap.insert({stmtNo, std::pair<std::string,
        std::shared_ptr<ExpressionNode>>(var, pattern)});
}

void PatternExtractorVisitor::transfer() {
    for (auto& [stmtNo, patternSet] : assignPatternMap) {
        assignAdder->addAssignPattern(stmtNo, patternSet.first, patternSet.second);
    }

    for (auto& [stmtNo, varSet] : ifPatternMap) {
        ifAdder->addIfPattern(stmtNo, varSet);
    }

    for (auto& [stmtNo, varSet] : whilePatternMap) {
        whileAdder->addWhilePattern(stmtNo, varSet);
    }
}
