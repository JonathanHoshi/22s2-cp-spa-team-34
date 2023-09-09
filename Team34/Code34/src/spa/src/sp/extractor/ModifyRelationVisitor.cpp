// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include <unordered_set>
#include <string>
#include "ModifyRelationVisitor.h"
#include "common/CollectionUtils.h"
#include "sp/node/IfNode.h"
#include "sp/node/ProcedureNode.h"
#include "sp/node/WhileNode.h"
#include "sp/node/AssignNode.h"
#include "sp/node/ReadNode.h"
#include "common/exceptions/TransverseError.h"

ModifyRelationVisitor::ModifyRelationVisitor(IModifiesAdder& adder) {
    this->adder = &adder;
}

void ModifyRelationVisitor::extract(VariableNode& node) {
    throw TransverseError{"ModifyExtractor should not be looking at a variable node"};
}

void ModifyRelationVisitor::extract(ConstantNode& node) {
    throw TransverseError{"ModifyExtractor should not be looking at a constant node"};
}

void ModifyRelationVisitor::extract(OperatorNode& node) {
    throw TransverseError{"ModifyExtractor should not be looking at a operator node"};
}

// statement nodes that do not modify
void ModifyRelationVisitor::extract(PrintNode& node) {}

void ModifyRelationVisitor::extract(ProcedureNode& node) {
    ExtractorVisitor::extract(node);
    std::unordered_set<std::string> set;
    mergeStmtList(set, *node.getStmtList());
    procedureMap.insert({node.getProcedureName(), set});
}

void ModifyRelationVisitor::extract(IfNode& node) {
    std::unordered_set<std::string> set;
    node.getThen()->accept(*this);
    mergeStmtList(set, *node.getThen());
    node.getElse()->accept(*this);
    mergeStmtList(set, *node.getElse());
    statementMap.insert({node.getStmtNumber(), set});
}

void ModifyRelationVisitor::extract(WhileNode& node) {
    node.getStmtLst()->accept(*this);
    std::unordered_set<std::string> set;
    mergeStmtList(set, *node.getStmtLst());
    statementMap.insert({node.getStmtNumber(), set});
}

void ModifyRelationVisitor::extract(AssignNode& node) {
    std::string var = node.getVariable()->getName();
    CollectionUtils::insert(statementMap, node.getStmtNumber(), var);
}

void ModifyRelationVisitor::extract(ReadNode& node) {
    std::string var = node.getVariable()->getName();
    CollectionUtils::insert(statementMap, node.getStmtNumber(), var);
}

void ModifyRelationVisitor::transfer() {
    for (auto& [procedure, variableSet] : procedureMap) {
        for (const std::string& variable : variableSet)
            adder->addVarP(procedure, variable);
    }
    for (auto& [stmtNo, variableSet] : statementMap) {
        for (const std::string& variable : variableSet) {
            adder->addVarS(stmtNo, variable);
        }
    }
}
