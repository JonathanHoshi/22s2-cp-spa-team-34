// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include <stdexcept>
#include "TopologicalSortVisitor.h"
#include "sp/node/CallNode.h"
#include "sp/node/ProcedureNode.h"
#include "sp/node/IfNode.h"
#include "sp/node/WhileNode.h"
#include "sp/node/RootNode.h"
#include "common/CollectionUtils.h"
#include "common/exceptions/TransverseError.h"
#include "common/exceptions/ParserError.h"

TopologicalSortVisitor::TopologicalSortVisitor() {}

void TopologicalSortVisitor::extract(VariableNode& node) {
    throw TransverseError{"TopologicalSortVisitor should not be looking at a variable node"};
}

void TopologicalSortVisitor::extract(ConstantNode& node) {
    throw TransverseError{"TopologicalSortVisitor should not be looking at a constant node"};
}

void TopologicalSortVisitor::extract(OperatorNode& node) {
    throw TransverseError{"TopologicalSortVisitor should not be looking at a operator node"};
}

// Statement nodes that do nothing in call
void TopologicalSortVisitor::extract(ReadNode& node) {}
void TopologicalSortVisitor::extract(PrintNode& node) {}
void TopologicalSortVisitor::extract(AssignNode& node) {}


void TopologicalSortVisitor::extract(CallNode& node) {
    prodCallStack.push(node.getProcedureName());
}

void TopologicalSortVisitor::extract(ProcedureNode& node) {
    ExtractorVisitor::extract(node);
    std::unordered_set<std::string> set;
    CollectionUtils::popStackIntoSet(prodCallStack, set);
    CollectionUtils::insert(callsMap, node.getProcedureName(), set);
}

void TopologicalSortVisitor::extract(IfNode& node) {
    node.getThen()->accept(*this);
    node.getElse()->accept(*this);
}

void TopologicalSortVisitor::extract(WhileNode& node) {
    node.getStmtLst()->accept(*this);
}

void TopologicalSortVisitor::begin(RootNode& node) {
    ExtractorVisitor::begin(node);
    populateToposort();
    node.sortProcedure(toposort);
}

void TopologicalSortVisitor::transfer() {}

void TopologicalSortVisitor::populateToposort() {
    std::unordered_map<std::string, bool> visited;
    initVisited(visited);
    for (auto prodSet : callsMap) {
        if (visited.at(prodSet.first) == true) {
            continue;
        }
        std::unordered_map<std::string, bool> currentVisited;
        initVisited(currentVisited);
        dfsRecurHelper(prodSet.first, visited, currentVisited);
    }
}

void TopologicalSortVisitor::dfsRecurHelper(std::string prodName,
    std::unordered_map<std::string, bool>& visited,
    std::unordered_map<std::string, bool>& currentVisited) {
    try {
        if (currentVisited.at(prodName) == true) {
            throw ParserError(ErrorStatus::SEMANTIC);
        }
    } catch (const std::out_of_range& e) {
        throw ParserError(ErrorStatus::SEMANTIC);
    }

    if (visited.at(prodName) == true) {
        return;
    }
    currentVisited.at(prodName) = true;
    visited.at(prodName) = true;
    auto set = callsMap.at(prodName);
    for (auto& call : set) {
        dfsRecurHelper(call, visited, currentVisited);
    }
    currentVisited.at(prodName) = false;
    toposort.push_back(prodName);
}

void TopologicalSortVisitor::initVisited(std::unordered_map<std::string, bool>& map) {
    for (auto prodSet : callsMap) {
        map.insert({prodSet.first, false});
    }
}
