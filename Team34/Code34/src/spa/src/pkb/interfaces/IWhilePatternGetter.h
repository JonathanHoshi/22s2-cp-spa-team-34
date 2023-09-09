// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
#include "di/IService.h"

class IWhilePatternGetter : public virtual IService {
public:
    ~IWhilePatternGetter() override = default;
    // Gets all stmt-var entries
    virtual std::unordered_map<int, std::unordered_set<std::string>> getStmtVarEntries() = 0;
    // Gets set of vars by stmtNum
    virtual std::unordered_set<std::string> getVarsByStmt(const int& stmtNum) = 0;
    // Gets set of stmts that has varName
    virtual std::unordered_set<int> getStmtsByVar(const std::string& varName) = 0;
    // Checks if stmtNum has varName
    virtual bool isValidPattern(const int& stmtNum, const std::string& varName) = 0;
    // Checks if there contains at least one while pattern
    virtual bool hasValidPattern() = 0;
    // Checks if there is an while pattern with stmtNum
    virtual bool hasValidPattern(const int& stmtNum) = 0;
    // Checks if there is an while pattern with varName
    virtual bool hasValidPattern(const std::string& varName) = 0;
};
