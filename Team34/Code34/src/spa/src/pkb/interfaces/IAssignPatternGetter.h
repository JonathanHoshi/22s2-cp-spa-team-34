// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <memory>
#include "di/IService.h"
#include "sp/node/ExpressionNode.h"

class IAssignPatternGetter : public virtual IService {
public:
    ~IAssignPatternGetter() override = default;

    /**
     * Get all assign pattern entries.
     * @return a unordered map which contains all the entries of assign pattern
     * std::pair
     */
    virtual std::unordered_map<int, std::pair<std::string, std::shared_ptr<ExpressionNode>>>
        getAssignPatterns() = 0;

    /**
     * Get corresponding assign pattern given the statement number. If it is not
     * existed in the table, return null.
     *
     * @param stmtNum the given stmt number
     * @return a pointer to the corresponding assignment pattern
     */
    virtual std::pair<std::string, std::shared_ptr<ExpressionNode>>
        getAssignPatternByStmtNum(const int& stmtNum) = 0;

    /**
     * Check whether a statement exists inside the assign pattern table
     *
     * @param stmtNum the given stmt number
     * @return whether the statement exists inside the assign pattern table
     */
    virtual bool isExisted(const int& stmtNum) = 0;

    /**
     * To check whether the given assign pattern AST is partial matched with the
     * AST corresponding to given stmtNum
     * stored inside the table.
     * @param stmtNum the statement number of the AST to compare with
     * @param varName the left hand of the expression
     * @param rightExpression the given assign pattern
     * @return whether the given assign pattern is partial matched with the target
     * one stored in the table
     */
    virtual bool
        isValidPartialPattern(const int& stmtNum, const std::string& varName,
            const std::shared_ptr<ExpressionNode>& rightExpression) = 0;
    /**
     * To check whether the given assign pattern AST is fully matched with the AST
     * corresponding to given stmtNum
     * stored inside the table.
     * @param stmtNum the statement number of the AST to compare with
     * @param varName the left hand of the expression
     * @param rightExpression the given assign pattern
     * @return whether the given assign pattern is partial matched with the target
     * one stored in the table
     */
    virtual bool
        isValidFullPattern(const int& stmtNum, const std::string& varName,
            const std::shared_ptr<ExpressionNode>& rightExpression) = 0;

    /**
     * To check whether the given stmtNum and varName is stored in table
     * @param stmtNum the statement number of the AST to compare with
     * @param varName the left hand of the expression
     * @return whether the given stmtNum and varName is stored in table
     */
    virtual bool isValidPattern(const int& stmtNum, const std::string& varName) = 0;
    virtual bool
        hasValidPartialPattern(const std::shared_ptr<ExpressionNode>& expression) = 0;
    virtual bool
        hasValidPartialPattern(const int& stmtNum,
            const std::shared_ptr<ExpressionNode>& expression) = 0;
    virtual bool
        hasValidPartialPattern(const std::string& varName,
            const std::shared_ptr<ExpressionNode>& expression) = 0;

    virtual bool
        hasValidFullPattern(const std::shared_ptr<ExpressionNode>& expression) = 0;
    virtual bool
        hasValidFullPattern(const int& stmtNum,
            const std::shared_ptr<ExpressionNode>& expression) = 0;
    virtual bool
        hasValidFullPattern(const std::string& varName,
            const std::shared_ptr<ExpressionNode>& expression) = 0;

    virtual bool hasValidPattern() = 0;
    virtual bool hasValidPattern(const int& stmtNum) = 0;
    virtual bool hasValidPattern(const std::string& varName) = 0;

    virtual std::unordered_map<int, std::string> getStmtsVarByValidPartialPattern(
        const std::shared_ptr<ExpressionNode>& expression) = 0;
    virtual std::unordered_map<int, std::string> getStmtsVarByValidFullPattern(
        const std::shared_ptr<ExpressionNode>& expression) = 0;
    virtual std::unordered_map<int, std::string> getStmtsVar() = 0;

    virtual std::unordered_set<int> getStmtsByVarValidPartialPattern(
        const std::string& varName, const std::shared_ptr<ExpressionNode>& expression) = 0;
    virtual std::unordered_set<int> getStmtsByVarValidFullPattern(
        const std::string& varName, const std::shared_ptr<ExpressionNode>& expression) = 0;
    virtual std::unordered_set<int> getStmtsByVar(const std::string& varName) = 0;

    virtual std::string getVarByStmtValidPartialPattern(
        const int& stmtNum, const std::shared_ptr<ExpressionNode>& expression) = 0;
    virtual std::string getVarByStmtValidFullPattern(
        const int& stmtNum, const std::shared_ptr<ExpressionNode>& expression) = 0;
    virtual std::string getVarByStmt(const int& stmtNum) = 0;
};
