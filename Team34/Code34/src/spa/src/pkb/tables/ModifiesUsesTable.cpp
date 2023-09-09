// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "ModifiesUsesTable.h"

// ---------- Statements ----------

std::unordered_map<int, std::unordered_set<std::string>> ModifiesUsesTable::getStmtVarEntries() {
    return this->stmtToVarEntries.getEntries();
}

std::unordered_set<std::string> ModifiesUsesTable::getVarsByStmt(const int& stmtNum) {
    return this->stmtToVarEntries.getValuesByKey(stmtNum);
}

std::unordered_set<int> ModifiesUsesTable::getStmtsByVar(const std::string& varName) {
    return this->varToStmtEntries.getValuesByKey(varName);
}

std::unordered_set<std::string> ModifiesUsesTable::getVarsInStmts() {
    return this->varToStmtEntries.getKeys();
}

std::unordered_set<int> ModifiesUsesTable::getStmts() {
    return this->stmtToVarEntries.getKeys();
}

bool ModifiesUsesTable::isAssociatedS(const int& stmtNum, const std::string& varName) {
    return this->stmtToVarEntries.hasKeyValue(stmtNum, varName);
}

bool ModifiesUsesTable::hasAssociatedS() {
    return this->stmtToVarEntries.getSize() > 0;
}

bool ModifiesUsesTable::hasAssociatedSByKey(const int& stmtNum) {
    return this->stmtToVarEntries.hasKey(stmtNum);
}

bool ModifiesUsesTable::hasAssociatedSByValue(const std::string& varName) {
    return this->varToStmtEntries.hasKey(varName);
}

void ModifiesUsesTable::addVarS(const int& stmtNum, const std::string& varName) {
    this->stmtToVarEntries.addEntry(stmtNum, varName);
    this->varToStmtEntries.addEntry(varName, stmtNum);
}

// ---------- Procedures ----------

std::unordered_map<std::string,
        std::unordered_set<std::string>> ModifiesUsesTable::getProcVarEntries() {
    return this->procToVarEntries.getEntries();
}

std::unordered_set<std::string> ModifiesUsesTable::getVarsByProc(const std::string& procName) {
    return this->procToVarEntries.getValuesByKey(procName);
}

std::unordered_set<std::string> ModifiesUsesTable::getProcsByVar(const std::string& varName) {
    return this->varToProcEntries.getValuesByKey(varName);
}

std::unordered_set<std::string> ModifiesUsesTable::getVarsInProcs() {
    return this->varToProcEntries.getKeys();
}

std::unordered_set<std::string> ModifiesUsesTable::getProcs() {
    return this->procToVarEntries.getKeys();
}

bool ModifiesUsesTable::isAssociatedP(const std::string& procName, const std::string& varName) {
    return this->procToVarEntries.hasKeyValue(procName, varName);
}

bool ModifiesUsesTable::hasAssociatedP() {
    return this->procToVarEntries.getSize() > 0;
}

bool ModifiesUsesTable::hasAssociatedPByKey(const std::string& procName) {
    return this->procToVarEntries.hasKey(procName);
}

bool ModifiesUsesTable::hasAssociatedPByValue(const std::string& varName) {
    return this->varToProcEntries.hasKey(varName);
}

void ModifiesUsesTable::addVarP(const std::string& procName, const std::string& varName) {
    this->procToVarEntries.addEntry(procName, varName);
    this->varToProcEntries.addEntry(varName, procName);
}
