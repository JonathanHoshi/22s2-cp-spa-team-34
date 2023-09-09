// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.
#pragma once

#include <unordered_map>
#include <unordered_set>
#include <string>
#include "pkb/base/BaseMapSet.h"
#include "pkb/interfaces/IIfPatternAdder.h"
#include "pkb/interfaces/IIfPatternGetter.h"

class IfPatternTable : public IIfPatternAdder, public IIfPatternGetter {
private:
    BaseMapSet<int, std::string> stmtToVarEntries;      // <stmt_num, var_names>
    BaseMapSet<std::string, int> varToStmtEntries;      // <var_name, stmt_nums>
public:
    std::unordered_map<int, std::unordered_set<std::string>> getStmtVarEntries() override;
    std::unordered_set<std::string> getVarsByStmt(const int& stmtNum) override;
    std::unordered_set<int> getStmtsByVar(const std::string& varName) override;
    bool isValidPattern(const int& stmtNum, const std::string& varName) override;
    bool hasValidPattern() override;
    bool hasValidPattern(const int& stmtNum) override;
    bool hasValidPattern(const std::string& varName) override;
    void addIfPattern(const int& stmtNum, const std::unordered_set<std::string>& val) override;
};
