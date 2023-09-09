// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "AssignPatternTable.h"
#include "common/ASTUtil.h"

std::unordered_map<int, std::pair<std::string,
    std::shared_ptr<ExpressionNode>>> AssignPatternTable::getAssignPatterns() {
    return assignPatterns.getEntries();
}

std::pair<std::string, std::shared_ptr<ExpressionNode>>
AssignPatternTable::getAssignPatternByStmtNum(const int& stmtNum) {
    return assignPatterns.getValByKey(stmtNum);
}

bool AssignPatternTable::isExisted(const int& stmtNum) {
    return assignPatterns.containKey(stmtNum);
}

bool AssignPatternTable::isValidPartialPattern(const int& stmtNum, const std::string& leftVal,
    const std::shared_ptr<ExpressionNode>& rightExpression) {
    if (!this->isExisted(stmtNum)) {
        return false;
    }
    std::pair<std::string, std::shared_ptr<ExpressionNode>> targetPattern =
        this->getAssignPatternByStmtNum(stmtNum);
    return targetPattern.first == leftVal &&
        ASTUtil::checkPartialEqual(*targetPattern.second.get(), *rightExpression.get());
}

bool AssignPatternTable::isValidFullPattern(const int& stmtNum, const std::string& leftVal,
    const std::shared_ptr<ExpressionNode>& rightExpression) {
    if (!this->isExisted(stmtNum)) {
        return false;
    }
    std::pair<std::string, std::shared_ptr<ExpressionNode>> targetPattern =
        this->getAssignPatternByStmtNum(stmtNum);
    return targetPattern.first == leftVal &&
        ASTUtil::checkFullEqual(*targetPattern.second.get(), *rightExpression.get());
}

bool AssignPatternTable::isValidPattern(const int& stmtNum, const std::string& leftVal) {
    if (!this->isExisted(stmtNum)) {
        return false;
    }
    std::pair<std::string, std::shared_ptr<ExpressionNode>> targetPattern =
        this->getAssignPatternByStmtNum(stmtNum);
    return targetPattern.first == leftVal;
}

bool AssignPatternTable::hasValidPartialPattern(const std::shared_ptr<ExpressionNode>& expression) {
    for (auto& [stmtNo, pair] : assignPatterns.getEntries()) {
        if (ASTUtil::checkPartialEqual(*pair.second, *expression)) {
            return true;
        }
    }
    return false;
}

bool AssignPatternTable::hasValidPartialPattern(const int& stmtNum,
    const std::shared_ptr<ExpressionNode>& expression) {
    return isExisted(stmtNum)
        && ASTUtil::checkPartialEqual(*getAssignPatternByStmtNum(stmtNum).second, *expression);
}

bool AssignPatternTable::hasValidPartialPattern(const std::string& varName,
    const std::shared_ptr<ExpressionNode>& expression) {
    for (auto& [stmtNo, pair] : assignPatterns.getEntries()) {
        if (pair.first == varName
            && ASTUtil::checkPartialEqual(*pair.second, *expression)) {
            return true;
        }
    }
    return false;
}

bool AssignPatternTable::hasValidFullPattern(const std::shared_ptr<ExpressionNode>& expression) {
    for (auto& [stmtNo, pair] : assignPatterns.getEntries()) {
        if (ASTUtil::checkFullEqual(*pair.second, *expression)) {
            return true;
        }
    }
    return false;
}

bool AssignPatternTable::hasValidFullPattern(const int& stmtNum,
    const std::shared_ptr<ExpressionNode>& expression) {
    return isExisted(stmtNum)
        && ASTUtil::checkFullEqual(*getAssignPatternByStmtNum(stmtNum).second, *expression);
}

bool AssignPatternTable::hasValidFullPattern(const std::string& varName,
    const std::shared_ptr<ExpressionNode>& expression) {
    for (auto& [stmtNo, pair] : assignPatterns.getEntries()) {
        if (pair.first == varName && ASTUtil::checkFullEqual(*pair.second, *expression)) {
            return true;
        }
    }
    return false;
}

bool AssignPatternTable::hasValidPattern() {
    return assignPatterns.getSize() != 0;
}

bool AssignPatternTable::hasValidPattern(const int& stmtNum) {
    return isExisted(stmtNum);
}

bool AssignPatternTable::hasValidPattern(const std::string& varName) {
    for (auto& [stmtNo, pair] : assignPatterns.getEntries()) {
        if (pair.first == varName) {
            return true;
        }
    }
    return false;
}

std::unordered_map<int, std::string> AssignPatternTable::getStmtsVarByValidPartialPattern(
    const std::shared_ptr<ExpressionNode>& expression) {
    std::unordered_map<int, std::string> result;

    for (auto& [stmtNo, pair] : assignPatterns.getEntries()) {
        if (ASTUtil::checkPartialEqual(*pair.second, *expression)) {
            result.emplace(stmtNo, pair.first);
        }
    }
    return result;
}

std::unordered_map<int, std::string> AssignPatternTable::getStmtsVarByValidFullPattern(
    const std::shared_ptr<ExpressionNode>& expression) {
    std::unordered_map<int, std::string> result;

    for (auto& [stmtNo, pair] : assignPatterns.getEntries()) {
        if (ASTUtil::checkFullEqual(*pair.second, *expression)) {
            result.emplace(stmtNo, pair.first);
        }
    }
    return result;
}

std::unordered_map<int, std::string> AssignPatternTable::getStmtsVar() {
    std::unordered_map<int, std::string> result;

    for (auto& [stmtNo, pair] : assignPatterns.getEntries()) {
        result.emplace(stmtNo, pair.first);
    }
    return result;
}

std::unordered_set<int>AssignPatternTable::getStmtsByVarValidPartialPattern(
    const std::string& varName, const std::shared_ptr<ExpressionNode>& expression) {
    std::unordered_set<int> result;

    for (auto& [stmtNo, pair] : assignPatterns.getEntries()) {
        if (pair.first == varName && ASTUtil::checkPartialEqual(*pair.second, *expression)) {
            result.emplace(stmtNo);
        }
    }
    return result;
}

std::unordered_set<int> AssignPatternTable::getStmtsByVarValidFullPattern(
    const std::string& varName, const std::shared_ptr<ExpressionNode>& expression) {
    std::unordered_set<int> result;

    for (auto& [stmtNo, pair] : assignPatterns.getEntries()) {
        if (pair.first == varName && *pair.second == *expression) {
            result.emplace(stmtNo);
        }
    }
    return result;
}

std::unordered_set<int> AssignPatternTable::getStmtsByVar(const std::string& varName) {
    std::unordered_set<int> result;

    for (auto& [stmtNo, pair] : assignPatterns.getEntries()) {
        if (pair.first == varName) {
            result.emplace(stmtNo);
        }
    }
    return result;
}

std::string AssignPatternTable::getVarByStmtValidPartialPattern(const int& stmtNum,
    const std::shared_ptr<ExpressionNode>& expression) {
    return isExisted(stmtNum)
        && ASTUtil::checkPartialEqual(*getAssignPatternByStmtNum(stmtNum).second, *expression)
        ? getAssignPatternByStmtNum(stmtNum).first
        : "";
}

std::string AssignPatternTable::getVarByStmtValidFullPattern(const int& stmtNum,
    const std::shared_ptr<ExpressionNode>& expression) {
    return isExisted(stmtNum)
        && ASTUtil::checkFullEqual(*getAssignPatternByStmtNum(stmtNum).second, *expression)
        ? getAssignPatternByStmtNum(stmtNum).first
        : "";
}

std::string AssignPatternTable::getVarByStmt(const int& stmtNum) {
    return isExisted(stmtNum)
        ? getAssignPatternByStmtNum(stmtNum).first
        : "";
}

void AssignPatternTable::addAssignPattern(const int& stmtNum,
    const std::string& leftVal, const std::shared_ptr<ExpressionNode>& expressionPtr) {
    assignPatterns.addEntry(stmtNum, leftVal, expressionPtr);
}
