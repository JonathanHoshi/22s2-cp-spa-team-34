#pragma once

#include "pkb/interfaces/IAssignPatternAdder.h"
#include "common/ASTUtil.h"
#include <string>
#include <unordered_map>



class StubAssignPatternAdder : public IAssignPatternAdder {
public:
    std::unordered_map<int, std::pair<std::string, std::shared_ptr<ExpressionNode>>> patternMap;

    bool checkPartialPattern(int stmtNo, std::string var, std::string exp) {
        if (!checkPatternExist(stmtNo, var))
            return false;

        std::shared_ptr<ExpressionNode> expNode = ASTUtil::convertToAST(exp);

        return ASTUtil::checkPartialEqual(*patternMap.at(stmtNo).second, *expNode);
    }


    bool checkFullPattern(int stmtNo, std::string var, std::string exp) {
        if (!checkPatternExist(stmtNo, var))
            return false;

        std::shared_ptr<ExpressionNode> expNode = ASTUtil::convertToAST(exp);

        return ASTUtil::checkFullEqual(*patternMap.at(stmtNo).second, *expNode);
    }

    bool checkPatternExist(int stmtNo, std::string var) {
        auto itor = patternMap.find(stmtNo);
        if (itor == patternMap.end())
            return false;
        if (itor->second.first != var)
            return false;
        return true;
    }

    void addAssignPattern(const int& stmtNum, const std::string& leftVal, const std::shared_ptr<ExpressionNode>& rightValPtr) override {
        std::pair<std::string, std::shared_ptr<ExpressionNode>> val = std::make_pair<>(leftVal, rightValPtr);
        patternMap.insert({stmtNum, val});
    }

};