// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once
#include <stack>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include "ExtractorVisitor.h"

class TopologicalSortVisitor : public ExtractorVisitor {
public:
    TopologicalSortVisitor();
    void extract(VariableNode& node) override;
    void extract(ConstantNode& node) override;
    void extract(OperatorNode& node) override;

    void extract(ReadNode& node) override;
    void extract(PrintNode& node) override;
    void extract(CallNode& node) override;
    void extract(IfNode& node) override;
    void extract(WhileNode& node) override;
    void extract(AssignNode& node) override;

    void extract(ProcedureNode& node) override;

    void begin(RootNode& node) override;
    void transfer() override;

protected:
    std::unordered_map<std::string, std::unordered_set<std::string>> callsMap;
    std::stack<std::string> prodCallStack;
    std::vector<std::string> toposort;

private:
    void dfsRecurHelper(std::string prodName, std::unordered_map<std::string, bool>& visited,
        std::unordered_map<std::string, bool>& currentVisited);
    void initVisited(std::unordered_map<std::string, bool>& map);
    void populateToposort();
};
