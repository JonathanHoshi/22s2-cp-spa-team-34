// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once
#include <stack>
#include <string>
#include "VariableRelationVisitor.h"
#include "pkb/interfaces/IUsesAdder.h"

class UsesRelationVisitor : public VariableRelationVisitor {
public:
    explicit UsesRelationVisitor(IUsesAdder& adder);
    void extract(VariableNode& node) override;
    void extract(ConstantNode& node) override;
    void extract(OperatorNode& node) override;

    void extract(ReadNode& node) override;
    void extract(PrintNode& node) override;
    void extract(IfNode& node) override;
    void extract(WhileNode& node) override;
    void extract(AssignNode& node) override;

    void extract(ProcedureNode& node) override;

    void transfer() override;

protected:
    IUsesAdder* adder;
    std::stack<std::string> varUseStack;
};

