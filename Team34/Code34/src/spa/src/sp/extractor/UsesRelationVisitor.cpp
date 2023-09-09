// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include <unordered_set>
#include "UsesRelationVisitor.h"
#include "common/CollectionUtils.h"
#include "sp/node/IfNode.h"
#include "sp/node/ProcedureNode.h"
#include "sp/node/WhileNode.h"
#include "sp/node/AssignNode.h"
#include "sp/node/PrintNode.h"
#include "sp/node/OperatorNode.h"

UsesRelationVisitor::UsesRelationVisitor(IUsesAdder& adder) {
    this->adder = &adder;
}

// Possible to visit a constant but nothing should be done
void UsesRelationVisitor::extract(ConstantNode& node) {}

void UsesRelationVisitor::extract(VariableNode& node) {
    varUseStack.push(node.getName());
}

void UsesRelationVisitor::extract(OperatorNode& node) {
    for (int i = 0; i < node.getNeighborCount(); i++) {
        node.getNeighbor(i)->accept(*this);
    }
}

// Statements that don't use
void UsesRelationVisitor::extract(ReadNode& node) {}

void UsesRelationVisitor::extract(IfNode& node) {
    std::unordered_set<std::string> set;
    node.getCondition()->accept(*this);
    CollectionUtils::popStackIntoSet(varUseStack, set);
    node.getThen()->accept(*this);
    mergeStmtList(set, *node.getThen());
    node.getElse()->accept(*this);
    mergeStmtList(set, *node.getElse());
    CollectionUtils::insert(statementMap, node.getStmtNumber(), set);
}

void UsesRelationVisitor::extract(WhileNode& node) {
    std::unordered_set<std::string> set;
    node.getCondition()->accept(*this);
    CollectionUtils::popStackIntoSet(varUseStack, set);
    node.getStmtLst()->accept(*this);
    mergeStmtList(set, *node.getStmtLst());
    CollectionUtils::insert(statementMap, node.getStmtNumber(), set);
}

void UsesRelationVisitor::extract(AssignNode& node) {
    std::unordered_set<std::string> set;
    node.getExpression()->accept(*this);
    CollectionUtils::popStackIntoSet(varUseStack, set);
    CollectionUtils::insert(statementMap, node.getStmtNumber(), set);
}

void UsesRelationVisitor::extract(PrintNode& node) {
    std::string var = node.getVariable()->getName();
    CollectionUtils::insert(statementMap, node.getStmtNumber(), var);
}

void UsesRelationVisitor::extract(ProcedureNode& node) {
    std::unordered_set<std::string> set;
    node.getStmtList()->accept(*this);
    mergeStmtList(set, *node.getStmtList());
    procedureMap.insert({node.getProcedureName(), set});
}

void UsesRelationVisitor::transfer() {
    for (auto& [procedure, variableSet] : procedureMap) {
        for (const std::string& variable : variableSet) {
            adder->addVarP(procedure, variable);
        }
    }

    for (auto& [stmtNo, variableSet] : statementMap) {
        for (const std::string& variable : variableSet) {
            adder->addVarS(stmtNo, variable);
        }
    }
}
