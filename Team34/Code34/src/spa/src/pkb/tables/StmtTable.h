// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once

#include <unordered_map>
#include <unordered_set>
#include <string>
#include "pkb/interfaces/IStmtAdder.h"
#include "pkb/interfaces/IStmtGetter.h"
#include "pkb/base/BaseSet.h"
#include "pkb/base/BaseMap.h"

class StmtTable : public IStmtAdder, public IStmtGetter {
private:
    BaseSet<int> readStmts;
    BaseSet<int> printStmts;
    BaseSet<int> assignStmts;
    BaseSet<int> callStmts;
    BaseSet<int> whileStmts;
    BaseSet<int> ifStmts;

    BaseMap<int, std::string> callProcs;
    BaseMap<int, std::string> printVars;
    BaseMap<int, std::string> readVars;

public:
    std::unordered_set<int> getAllStmts() override;
    std::unordered_set<int> getReadStmts() override;
    std::unordered_set<int> getPrintStmts() override;
    std::unordered_set<int> getAssignStmts() override;
    std::unordered_set<int> getCallStmts() override;
    std::unordered_set<int> getWhileStmts() override;
    std::unordered_set<int> getIfStmts() override;

    bool isReadStmt(const int& stmtNum) override;
    bool isPrintStmt(const int& stmtNum) override;
    bool isAssignStmt(const int& stmtNum) override;
    bool isCallStmt(const int& stmtNum) override;
    bool isWhileStmt(const int& stmtNum) override;
    bool isIfStmt(const int& stmtNum) override;

    void addReadStmt(const int& stmtNum, const std::string& varName) override;
    void addPrintStmt(const int& stmtNum, const std::string& varName) override;
    void addAssignStmt(const int& stmtNum) override;
    void addCallStmt(const int& stmtNum, const std::string& procName) override;
    void addWhileStmt(const int& stmtNum) override;
    void addIfStmt(const int& stmtNum) override;

    void addReadStmts(const std::unordered_map<int, std::string>& stmtSet) override;
    void addPrintStmts(const std::unordered_map<int, std::string>& stmtSet) override;
    void addAssignStmts(const std::unordered_set<int>& stmtSet) override;
    void addCallStmts(const std::unordered_map<int, std::string>& stmtSet) override;
    void addWhileStmts(const std::unordered_set<int>& stmtSet) override;
    void addIfStmts(const std::unordered_set<int>& stmtSet) override;

    std::unordered_map<int, std::string> getCallProcEntries() override;
    std::unordered_map<int, std::string> getPrintVarEntries() override;
    std::unordered_map<int, std::string> getReadVarEntries() override;
    std::string getCallProc(const int& stmtNum) override;
    std::string getPrintVar(const int& stmtNum) override;
    std::string getReadVar(const int& stmtNum) override;
};
