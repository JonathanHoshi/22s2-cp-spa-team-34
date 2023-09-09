// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <string>
#include "ExtractorVisitor.h"
#include "pkb/interfaces/ICallsAdder.h"

class CallsExtractorVisitor : public ExtractorVisitor {
public:
    explicit CallsExtractorVisitor(ICallsAdder& adder);
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

    void transfer() override;

protected:
    std::unordered_map<std::string, std::unordered_set<std::string>> callsMap;
    std::unordered_map<std::string, std::unordered_set<std::string>> callsTMap;
    std::stack<std::string> prodCallStack;

private:
    ICallsAdder* adder;
};
