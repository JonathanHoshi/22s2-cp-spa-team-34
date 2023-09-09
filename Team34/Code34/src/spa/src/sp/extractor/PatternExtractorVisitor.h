// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once

#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <string>
#include <utility>
#include <memory>

#include "ExtractorVisitor.h"
#include "pkb/interfaces/IAssignPatternAdder.h"
#include "pkb/interfaces/IIfPatternAdder.h"
#include "pkb/interfaces/IWhilePatternAdder.h"

class PatternExtractorVisitor : public ExtractorVisitor {
public:
    PatternExtractorVisitor(IAssignPatternAdder& assignAdder,
        IIfPatternAdder& ifAdder, IWhilePatternAdder& whileAdder);
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
    IAssignPatternAdder* assignAdder;
    IIfPatternAdder* ifAdder;
    IWhilePatternAdder* whileAdder;

    std::stack<std::string> expressionVars;
    std::unordered_map<int, std::pair<std::string,
        std::shared_ptr<ExpressionNode>>> assignPatternMap;
    std::unordered_map<int, std::unordered_set<std::string>> ifPatternMap;
    std::unordered_map<int, std::unordered_set<std::string>> whilePatternMap;
};

