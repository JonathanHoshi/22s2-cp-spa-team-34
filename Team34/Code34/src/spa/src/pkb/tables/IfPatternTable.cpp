// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.
#include "IfPatternTable.h"

std::unordered_map<int, std::unordered_set<std::string>>
IfPatternTable::getStmtVarEntries() {
    return this->stmtToVarEntries.getEntries();
}

std::unordered_set<std::string>
IfPatternTable::getVarsByStmt(const int& stmtNum) {
    return this->stmtToVarEntries.getValuesByKey(stmtNum);
}

std::unordered_set<int>
IfPatternTable::getStmtsByVar(const std::string& varName) {
    return this->varToStmtEntries.getValuesByKey(varName);
}

bool IfPatternTable::isValidPattern(const int& stmtNum,
    const std::string& varName) {
    return this->stmtToVarEntries.hasKeyValue(stmtNum, varName);
}

bool IfPatternTable::hasValidPattern() {
    return this->stmtToVarEntries.getSize() > 0;
}

bool IfPatternTable::hasValidPattern(const int& stmtNum) {
    return this->stmtToVarEntries.hasKey(stmtNum);
}

bool IfPatternTable::hasValidPattern(const std::string& varName) {
    return this->varToStmtEntries.hasKey(varName);
}

void IfPatternTable::addIfPattern(const int& stmtNum,
    const std::unordered_set<std::string>& val) {
    for (std::string varName : val) {
        this->stmtToVarEntries.addEntry(stmtNum, varName);
        this->varToStmtEntries.addEntry(varName, stmtNum);
    }
}
