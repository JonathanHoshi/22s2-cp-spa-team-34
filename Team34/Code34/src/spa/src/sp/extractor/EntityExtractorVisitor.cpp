// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "EntityExtractorVisitor.h"
#include "sp/node/CallNode.h"
#include "sp/node/ProcedureNode.h"
#include "sp/node/IfNode.h"
#include "sp/node/WhileNode.h"
#include "sp/node/ConstantNode.h"
#include "sp/node/VariableNode.h"
#include "sp/node/OperatorNode.h"
#include "sp/node/AssignNode.h"
#include "sp/node/ReadNode.h"
#include "sp/node/PrintNode.h"

EntityExtractorVisitor::EntityExtractorVisitor(IStmtAdder& stmtAdder,
    IProcAdder& procAdder, IConstAdder& constAdder, IVarAdder& varAdder) {
    this->stmtAdder = &stmtAdder;
    this->procAdder = &procAdder;
    this->constAdder = &constAdder;
    this->varAdder = &varAdder;
}

void EntityExtractorVisitor::extract(ConstantNode& node) {
    constantLst.insert(node.getValue());
}

void EntityExtractorVisitor::extract(VariableNode& node) {
    variableLst.insert(node.getName());
}

void EntityExtractorVisitor::extract(OperatorNode& node) {
    for (int i = 0; i < node.getNeighborCount(); i++) {
        node.getNeighbor(i)->accept(*this);
    }
}

void EntityExtractorVisitor::extract(CallNode& node) {
    callList.insert({node.getStmtNumber(), node.getProcedureName()});
}

void EntityExtractorVisitor::extract(IfNode& node) {
    ifList.insert(node.getStmtNumber());
    node.getCondition()->accept(*this);
    node.getThen()->accept(*this);
    node.getElse()->accept(*this);
}

void EntityExtractorVisitor::extract(WhileNode& node) {
    whileList.insert(node.getStmtNumber());
    node.getCondition()->accept(*this);
    node.getStmtLst()->accept(*this);
}

void EntityExtractorVisitor::extract(AssignNode& node) {
    assignList.insert(node.getStmtNumber());
    node.getVariable()->accept(*this);
    node.getExpression()->accept(*this);
}

void EntityExtractorVisitor::extract(ReadNode& node) {
    readLst.insert({node.getStmtNumber(), node.getVariable()->getName()});
    node.getVariable()->accept(*this);
}

void EntityExtractorVisitor::extract(PrintNode& node) {
    printLst.insert({node.getStmtNumber(), node.getVariable()->getName()});
    node.getVariable()->accept(*this);
}

void EntityExtractorVisitor::extract(ProcedureNode& node) {
    ExtractorVisitor::extract(node);
    procedureLst.insert(node.getProcedureName());
}
void EntityExtractorVisitor::transfer() {
    constAdder->addConsts(constantLst);
    procAdder->addProcs(procedureLst);
    varAdder->addVars(variableLst);
    stmtAdder->addAssignStmts(assignList);
    stmtAdder->addCallStmts(callList);
    stmtAdder->addPrintStmts(printLst);
    stmtAdder->addReadStmts(readLst);
    stmtAdder->addIfStmts(ifList);
    stmtAdder->addWhileStmts(whileList);
}
