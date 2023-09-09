// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.
#include "WhilePatternTable.h"

std::unordered_map<int,
    std::unordered_set<std::string>> WhilePatternTable::getStmtVarEntries() {
    return this->stmtToVarEntries.getEntries();
}

std::unordered_set<std::string>
WhilePatternTable::getVarsByStmt(const int& stmtNum) {
    return this->stmtToVarEntries.getValuesByKey(stmtNum);
}

std::unordered_set<int>
WhilePatternTable::getStmtsByVar(const std::string& varName) {
    return this->varToStmtEntries.getValuesByKey(varName);
}

bool WhilePatternTable::isValidPattern(const int& stmtNum,
    const std::string& varName) {
    return this->stmtToVarEntries.hasKeyValue(stmtNum, varName);
}

bool WhilePatternTable::hasValidPattern() {
    return this->stmtToVarEntries.getSize() > 0;
}

bool WhilePatternTable::hasValidPattern(const int& stmtNum) {
    return this->stmtToVarEntries.hasKey(stmtNum);
}

bool WhilePatternTable::hasValidPattern(const std::string& varName) {
    return this->varToStmtEntries.hasKey(varName);
}

void WhilePatternTable::addWhilePattern(const int& stmtNum,
    const std::unordered_set<std::string>& val) {
    for (std::string varName : val) {
        this->stmtToVarEntries.addEntry(stmtNum, varName);
        this->varToStmtEntries.addEntry(varName, stmtNum);
    }
}
