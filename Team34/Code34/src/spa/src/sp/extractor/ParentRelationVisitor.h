// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once

#include <unordered_map>
#include <unordered_set>
#include "ExtractorVisitor.h"
#include "pkb/interfaces/IParentAdder.h"

class ParentRelationVisitor : public ExtractorVisitor {
public:
    explicit ParentRelationVisitor(IParentAdder& adder);
    void extract(VariableNode& node) override;
    void extract(ConstantNode& node) override;
    void extract(OperatorNode& node) override;

    void extract(ReadNode& node) override;
    void extract(PrintNode& node) override;
    void extract(CallNode& node) override;
    void extract(IfNode& node) override;
    void extract(WhileNode& node) override;
    void extract(AssignNode& node) override;

    void transfer() override;

protected:
    IParentAdder* adder;
    std::unordered_map<int, std::unordered_set<int>> parentsMap;
    std::unordered_map<int, std::unordered_set<int>> parentsTMap;
    void mergeChildren(const int& parentStmtNumber, StmtLstNode& stmtList);
};
