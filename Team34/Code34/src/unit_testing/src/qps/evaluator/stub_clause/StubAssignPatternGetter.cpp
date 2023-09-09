#pragma once

#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "common/ASTUtil.h"
#include "common/CollectionUtils.h"
#include "pkb/interfaces/IAssignPatternGetter.h"



class StubAssignPatternGetter : public IAssignPatternGetter {
private:
    std::unordered_map<int, std::pair<std::string, std::shared_ptr<ExpressionNode>>> assignPatternEntries;

public:
    void setAssignPatternEntries(std::unordered_map<int, std::pair<std::string, std::shared_ptr<ExpressionNode>>>& assignPatternEntries) {
        this->assignPatternEntries = assignPatternEntries;
    }

    virtual std::unordered_map<int, std::pair<std::string, std::shared_ptr<ExpressionNode>>> getAssignPatterns() override {
        return this->assignPatternEntries;
    }

    virtual std::pair<std::string, std::shared_ptr<ExpressionNode>> getAssignPatternByStmtNum(const int& stmtNum) override {
        if (isExisted(stmtNum)) {
            return assignPatternEntries[stmtNum];
        }

        return std::pair<std::string, std::shared_ptr<ExpressionNode>>();
    }

    virtual bool isExisted(const int& stmtNum) override {
        return assignPatternEntries.find(stmtNum) != assignPatternEntries.end();
    }

    virtual bool isValidPartialPattern(const int& stmtNum, const std::string& leftVal, const std::shared_ptr<ExpressionNode>& rightExpression) override {
        auto rhs = getAssignPatternByStmtNum(stmtNum);

        return rhs.first == leftVal && ASTUtil::checkPartialEqual(*rhs.second, *rightExpression);
    }

    virtual bool isValidFullPattern(const int& stmtNum, const std::string& leftVal, const std::shared_ptr<ExpressionNode>& rightExpression) override {
        auto rhs = getAssignPatternByStmtNum(stmtNum);

        return rhs.first == leftVal && ASTUtil::checkFullEqual(*rhs.second, *rightExpression);
    }

    virtual bool isValidPattern(const int& stmtNum, const std::string& leftVal) override {
        auto rhs = getAssignPatternByStmtNum(stmtNum);

        return rhs.first == leftVal;
    }

    virtual bool hasValidPartialPattern(const std::shared_ptr<ExpressionNode>& expression) override {
        for (auto& [stmtNo, pair] : assignPatternEntries) {
            if (ASTUtil::checkPartialEqual(*pair.second, *expression)) {
                return true;
            }
        }
        return false;
    }

    virtual bool hasValidPartialPattern(const int& stmtNum, const std::shared_ptr<ExpressionNode>& expression) override {
        return isExisted(stmtNum) && ASTUtil::checkPartialEqual(*getAssignPatternByStmtNum(stmtNum).second, *expression);
    }

    virtual bool hasValidPartialPattern(const std::string& varName, const std::shared_ptr<ExpressionNode>& expression) override {
        for (auto& [stmtNo, pair] : assignPatternEntries) {
            if (pair.first == varName && ASTUtil::checkPartialEqual(*pair.second, *expression)) {
                return true;
            }
        }
        return false;
    }

    virtual bool hasValidFullPattern(const std::shared_ptr<ExpressionNode>& expression) override {
        for (auto& [stmtNo, pair] : assignPatternEntries) {
            if (pair.second == (expression)) {
                return true;
            }
        }
        return false;
    }

    virtual bool hasValidFullPattern(const int& stmtNum, const std::shared_ptr<ExpressionNode>& expression) override {
        return isExisted(stmtNum) && ASTUtil::checkFullEqual(*getAssignPatternByStmtNum(stmtNum).second, *expression);
    }

    virtual bool hasValidFullPattern(const std::string& varName, const std::shared_ptr<ExpressionNode>& expression) override {
        for (auto& [stmtNo, pair] : assignPatternEntries) {
            if (pair.first == varName && ASTUtil::checkFullEqual(*pair.second, *expression)) {
                return true;
            }
        }
        return false;
    }

    virtual bool hasValidPattern() override {
        return !assignPatternEntries.empty();
    }

    virtual bool hasValidPattern(const int& stmtNum) override {
        return isExisted(stmtNum);
    }
    virtual bool hasValidPattern(const std::string& varName) override {
        for (auto& [stmtNo, pair] : assignPatternEntries) {
            if (pair.first == varName) {
                return true;
            }
        }
        return false;
    }

    virtual std::unordered_map<int, std::string> getStmtsVarByValidPartialPattern(const std::shared_ptr<ExpressionNode>& expression) override {
        std::unordered_map<int, std::string> result;

        for (auto& [stmtNo, pair] : assignPatternEntries) {
            if (ASTUtil::checkPartialEqual(*pair.second, *expression)) {
                result.emplace(stmtNo, pair.first);
            }
        }
        return result;
    }

    virtual std::unordered_map<int, std::string> getStmtsVarByValidFullPattern(const std::shared_ptr<ExpressionNode>& expression) override {
        std::unordered_map<int, std::string> result;

        for (auto& [stmtNo, pair] : assignPatternEntries) {
            if (ASTUtil::checkFullEqual(*pair.second, *expression)) {
                result.emplace(stmtNo, pair.first);
            }
        }
        return result;
    }

    virtual std::unordered_map<int, std::string> getStmtsVar() override {
        std::unordered_map<int, std::string> result;

        for (auto& [stmtNo, pair] : assignPatternEntries) {
            result.emplace(stmtNo, pair.first);
        }
        return result;
    }

    virtual std::unordered_set<int> getStmtsByVarValidPartialPattern(const std::string& varName, const std::shared_ptr<ExpressionNode>& expression) override {
        std::unordered_set<int> result;

        for (auto& [stmtNo, pair] : assignPatternEntries) {
            if (pair.first == varName && ASTUtil::checkPartialEqual(*pair.second, *expression)) {
                result.emplace(stmtNo);
            }
        }
        return result;
    }

    virtual std::unordered_set<int> getStmtsByVarValidFullPattern(const std::string& varName, const std::shared_ptr<ExpressionNode>& expression) override {
        std::unordered_set<int> result;

        for (auto& [stmtNo, pair] : assignPatternEntries) {
            if (pair.first == varName && ASTUtil::checkFullEqual(*pair.second, *expression)) {
                result.emplace(stmtNo);
            }
        }
        return result;
    }

    virtual std::unordered_set<int> getStmtsByVar(const std::string& varName) override {
        std::unordered_set<int> result;

        for (auto& [stmtNo, pair] : assignPatternEntries) {
            if (pair.first == varName) {
                result.emplace(stmtNo);
            }
        }
        return result;
    }

    virtual std::string getVarByStmtValidPartialPattern(const int& stmtNum, const std::shared_ptr<ExpressionNode>& expression) override {
        return isExisted(stmtNum) && ASTUtil::checkPartialEqual(*getAssignPatternByStmtNum(stmtNum).second, *expression)
            ? getAssignPatternByStmtNum(stmtNum).first
            : throw std::runtime_error("Should not be getting from a stmt number that is not found in table");
    }

    virtual std::string getVarByStmtValidFullPattern(const int& stmtNum, const std::shared_ptr<ExpressionNode>& expression) override {
        return isExisted(stmtNum) && ASTUtil::checkFullEqual(*getAssignPatternByStmtNum(stmtNum).second, *expression)
            ? getAssignPatternByStmtNum(stmtNum).first
            : throw std::runtime_error("Should not be getting from a stmt number that is not found in table");
    }

    virtual std::string getVarByStmt(const int& stmtNum) override {
        return isExisted(stmtNum)
            ? getAssignPatternByStmtNum(stmtNum).first
            : throw std::runtime_error("Should not be getting from a stmt number that is not found in table");
    }
};
