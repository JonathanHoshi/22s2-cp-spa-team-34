// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once

#include <stack>
#include <unordered_map>
#include <unordered_set>
#include "ExtractorVisitor.h"
#include "pkb/interfaces/INextAdder.h"

class CFGExtractorVisitor : public ExtractorVisitor {
public:
    explicit CFGExtractorVisitor(INextAdder& adder);
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
    std::unordered_map<int, std::unordered_set<int>> cfg;
    std::unordered_set<int> previousStmts;

    void insertAllStmts(int stmtNo);

private:
    INextAdder* adder;
};
