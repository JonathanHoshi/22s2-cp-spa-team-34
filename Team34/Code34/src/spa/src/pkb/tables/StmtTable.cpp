// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "StmtTable.h"
#include "common/CollectionUtils.h"

// Get

std::unordered_set<int> StmtTable::getReadStmts() {
    return readStmts.getEntries();
}

std::unordered_set<int> StmtTable::getPrintStmts() {
    return printStmts.getEntries();
}

std::unordered_set<int> StmtTable::getAssignStmts() {
    return assignStmts.getEntries();
}

std::unordered_set<int> StmtTable::getCallStmts() {
    return callStmts.getEntries();
}

std::unordered_set<int> StmtTable::getWhileStmts() {
    return whileStmts.getEntries();
}

std::unordered_set<int> StmtTable::getIfStmts() {
    return ifStmts.getEntries();
}

std::unordered_set<int> StmtTable::getAllStmts() {
    std::unordered_set<int> stmts;
    std::unordered_set<int> readStmts = getReadStmts();
    std::unordered_set<int> printStmts = getPrintStmts();
    std::unordered_set<int> assignStmts = getAssignStmts();
    std::unordered_set<int> callStmts = getCallStmts();
    std::unordered_set<int> whileStmts = getWhileStmts();
    std::unordered_set<int> ifStmts = getIfStmts();
    CollectionUtils::merge(stmts, readStmts);
    CollectionUtils::merge(stmts, printStmts);
    CollectionUtils::merge(stmts, assignStmts);
    CollectionUtils::merge(stmts, callStmts);
    CollectionUtils::merge(stmts, whileStmts);
    CollectionUtils::merge(stmts, ifStmts);
    return stmts;
}

// If

bool StmtTable::isReadStmt(const int& stmtNum) {
    return readStmts.containKey(stmtNum);
}

bool StmtTable::isPrintStmt(const int& stmtNum) {
    return printStmts.containKey(stmtNum);
}

bool StmtTable::isAssignStmt(const int& stmtNum) {
    return assignStmts.containKey(stmtNum);
}

bool StmtTable::isCallStmt(const int& stmtNum) {
    return callStmts.containKey(stmtNum);
}

bool StmtTable::isWhileStmt(const int& stmtNum) {
    return whileStmts.containKey(stmtNum);
}

bool StmtTable::isIfStmt(const int& stmtNum) {
    return ifStmts.containKey(stmtNum);
}

// Add

void StmtTable::addReadStmt(const int& stmtNum, const std::string& varName) {
    readStmts.addEntry(stmtNum);
    readVars.addEntry(stmtNum, varName);
}

void StmtTable::addPrintStmt(const int& stmtNum, const std::string& varName) {
    printStmts.addEntry(stmtNum);
    printVars.addEntry(stmtNum, varName);
}

void StmtTable::addAssignStmt(const int& stmtNum) {
    assignStmts.addEntry(stmtNum);
}

void StmtTable::addCallStmt(const int& stmtNum, const std::string& procName) {
    callStmts.addEntry(stmtNum);
    callProcs.addEntry(stmtNum, procName);
}

void StmtTable::addWhileStmt(const int& stmtNum) {
    whileStmts.addEntry(stmtNum);
}

void StmtTable::addIfStmt(const int& stmtNum) {
    ifStmts.addEntry(stmtNum);
}

void StmtTable::addReadStmts(const std::unordered_map<int, std::string>& stmtSet) {
    for (const auto& stmt : stmtSet) {
        this->addReadStmt(stmt.first, stmt.second);
    }
}

void StmtTable::addPrintStmts(const std::unordered_map<int, std::string>& stmtSet) {
    for (const auto& stmt : stmtSet) {
        this->addPrintStmt(stmt.first, stmt.second);
    }
}

void StmtTable::addAssignStmts(const std::unordered_set<int>& stmtSet) {
    for (const auto& stmtNum : stmtSet) {
        this->addAssignStmt(stmtNum);
    }
}

void StmtTable::addCallStmts(const std::unordered_map<int, std::string>& stmtSet) {
    for (const auto& stmt : stmtSet) {
        this->addCallStmt(stmt.first, stmt.second);
    }
}

void StmtTable::addWhileStmts(const std::unordered_set<int>& stmtSet) {
    for (const auto& stmtNum : stmtSet) {
        this->addWhileStmt(stmtNum);
    }
}

void StmtTable::addIfStmts(const std::unordered_set<int>& stmtSet) {
    for (const auto& stmtNum : stmtSet) {
        this->addIfStmt(stmtNum);
    }
}

// Attributes

std::unordered_map<int, std::string> StmtTable::getCallProcEntries() {
    return callProcs.getEntries();
}

std::unordered_map<int, std::string> StmtTable::getPrintVarEntries() {
    return printVars.getEntries();
}

std::unordered_map<int, std::string> StmtTable::getReadVarEntries() {
    return readVars.getEntries();
}

std::string StmtTable::getCallProc(const int& stmtNum) {
    return callProcs.getValueByKey(stmtNum);
}

std::string StmtTable::getPrintVar(const int& stmtNum) {
    return printVars.getValueByKey(stmtNum);
}

std::string StmtTable::getReadVar(const int& stmtNum) {
    return readVars.getValueByKey(stmtNum);
}
