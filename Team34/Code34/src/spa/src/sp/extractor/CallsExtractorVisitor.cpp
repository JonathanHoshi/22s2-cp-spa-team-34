// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include <stdexcept>
#include "CallsExtractorVisitor.h"
#include "sp/node/CallNode.h"
#include "sp/node/ProcedureNode.h"
#include "sp/node/IfNode.h"
#include "sp/node/WhileNode.h"
#include "sp/node/RootNode.h"
#include "common/CollectionUtils.h"
#include "common/exceptions/TransverseError.h"
#include "common/exceptions/ParserError.h"

CallsExtractorVisitor::CallsExtractorVisitor(ICallsAdder& adder) {
    this->adder = &adder;
}

void CallsExtractorVisitor::extract(VariableNode& node) {
    throw TransverseError{"CallsExtractor should not be looking at a variable node"};
}

void CallsExtractorVisitor::extract(ConstantNode& node) {
    throw TransverseError{"CallsExtractor should not be looking at a constant node"};
}

void CallsExtractorVisitor::extract(OperatorNode& node) {
    throw TransverseError{"CallsExtractor should not be looking at a operator node"};
}

// Statement nodes that do nothing in call
void CallsExtractorVisitor::extract(ReadNode& node) {}
void CallsExtractorVisitor::extract(PrintNode& node) {}
void CallsExtractorVisitor::extract(AssignNode& node) {}


void CallsExtractorVisitor::extract(CallNode& node) {
    if (!CollectionUtils::find(callsMap, node.getProcedureName())) {
        throw TransverseError{"AST is not sorted topologically"};
    }
    prodCallStack.push(node.getProcedureName());
}

void CallsExtractorVisitor::extract(ProcedureNode& node) {
    ExtractorVisitor::extract(node);
    std::unordered_set<std::string> set;
    while (!prodCallStack.empty()) {
        set.insert(prodCallStack.top());
        prodCallStack.pop();
    }
    CollectionUtils::insert(callsMap, node.getProcedureName(), set);
    for (auto& proc : set) {
        CollectionUtils::insert(callsTMap, node.getProcedureName(), callsTMap.at(proc));
    }
    CollectionUtils::insert(callsTMap, node.getProcedureName(), set);
}

void CallsExtractorVisitor::extract(IfNode& node) {
    node.getThen()->accept(*this);
    node.getElse()->accept(*this);
}

void CallsExtractorVisitor::extract(WhileNode& node) {
    node.getStmtLst()->accept(*this);
}

void CallsExtractorVisitor::transfer() {
    for (auto prodSet : callsMap) {
        std::string fromProd = prodSet.first;
        for (auto toProd : prodSet.second) {
            adder->addCalls(fromProd, toProd);
        }
    }
    for (auto prodSet : callsTMap) {
        std::string fromProd = prodSet.first;
        for (auto toProd : prodSet.second) {
            adder->addCallsT(fromProd, toProd);
        }
    }
}
