// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once

#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <memory>
#include <string>

#include "pkb/interfaces/IAssignPatternAdder.h"
#include "pkb/interfaces/IAssignPatternGetter.h"
#include "pkb/base/BasePairMap.h"
#include "pkb/base/BaseSet.h"
#include "common/ASTUtil.h"
#include "sp/node/ExpressionNode.h"

class AssignPatternTable : public IAssignPatternAdder, public IAssignPatternGetter {
private:
    // stmt_num, varName, Expression
    BasePairMap<int, std::string, std::shared_ptr<ExpressionNode>> assignPatterns;

public:
    std::unordered_map<int, std::pair<std::string,
        std::shared_ptr<ExpressionNode>>> getAssignPatterns() override;
    std::pair<std::string,
        std::shared_ptr<ExpressionNode>> getAssignPatternByStmtNum(const int& stmtNum) override;
    bool isExisted(const int& stmtNum) override;
    bool isValidPartialPattern(const int& stmtNum, const std::string& varName,
        const std::shared_ptr<ExpressionNode>& expression) override;
    bool isValidFullPattern(const int& stmtNum, const std::string& varName,
        const std::shared_ptr<ExpressionNode>& expression) override;
    bool isValidPattern(const int& stmtNum, const std::string& varName) override;

    bool hasValidPartialPattern(const std::shared_ptr<ExpressionNode>& expression) override;
    bool hasValidPartialPattern(const int& stmtNum,
        const std::shared_ptr<ExpressionNode>& expression) override;
    bool hasValidPartialPattern(const std::string& varName,
        const std::shared_ptr<ExpressionNode>& expression) override;

    bool hasValidFullPattern(const std::shared_ptr<ExpressionNode>& expression) override;
    bool hasValidFullPattern(const int& stmtNum,
        const std::shared_ptr<ExpressionNode>& expression) override;
    bool hasValidFullPattern(const std::string& varName,
        const std::shared_ptr<ExpressionNode>& expression) override;

    bool hasValidPattern() override;
    bool hasValidPattern(const int& stmtNum) override;
    bool hasValidPattern(const std::string& varName) override;

    std::unordered_map<int, std::string>
        getStmtsVarByValidPartialPattern(const std::shared_ptr<ExpressionNode>& expression)
        override;
    std::unordered_map<int, std::string>
        getStmtsVarByValidFullPattern(const std::shared_ptr<ExpressionNode>& expression) override;
    std::unordered_map<int, std::string> getStmtsVar() override;

    std::unordered_set<int>getStmtsByVarValidPartialPattern(const std::string& varName,
        const std::shared_ptr<ExpressionNode>& expression) override;
    std::unordered_set<int> getStmtsByVarValidFullPattern(const std::string& varName,
        const std::shared_ptr<ExpressionNode>& expression) override;
    std::unordered_set<int> getStmtsByVar(const std::string& varName) override;

    std::string getVarByStmtValidPartialPattern(const int& stmtNum,
        const std::shared_ptr<ExpressionNode>& expression) override;
    std::string getVarByStmtValidFullPattern(const int& stmtNum,
        const std::shared_ptr<ExpressionNode>& expression) override;
    std::string getVarByStmt(const int& stmtNum) override;

    void addAssignPattern(const int& stmtNum, const std::string& varName,
        const std::shared_ptr<ExpressionNode>& expressionPtr) override;
};
