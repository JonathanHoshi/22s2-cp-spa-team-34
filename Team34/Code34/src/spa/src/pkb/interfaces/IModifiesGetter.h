// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
#include "di/IService.h"

class IModifiesGetter : public virtual IService {
public:
    ~IModifiesGetter() override = default;

    // ---------- Modifies: Statements ----------
    // Gets all stmt-modifies-var entries
    virtual std::unordered_map<int, std::unordered_set<std::string>> getStmtVarEntries() = 0;
    // Gets var modified by stmtNum
    virtual std::unordered_set<std::string> getVarsByStmt(const int& stmtNum) = 0;
    // Gets set of stmts that modify varName
    virtual std::unordered_set<int> getStmtsByVar(const std::string& varName) = 0;
    // Gets set of vars that are modified by some stmt
    virtual std::unordered_set<std::string> getVarsInStmts() = 0;
    // Gets set of stmts that modifies some var
    virtual std::unordered_set<int> getStmts() = 0;
    // Checks if stmtNum modifies varName
    virtual bool isAssociatedS(const int& stmtNum, const std::string& varName) = 0;
    // Checks if there contains at least one modifies S
    virtual bool hasAssociatedS() = 0;
    // Checks if stmtNum is modifies S
    virtual bool hasAssociatedSByKey(const int& stmtNum) = 0;
    // Checks if varName is modifies S
    virtual bool hasAssociatedSByValue(const std::string& varName) = 0;

    // ---------- Modifies: Procedures ----------
    // Gets all proc-modifies-var entries
    virtual std::unordered_map<std::string, std::unordered_set<std::string>>
        getProcVarEntries() = 0;
    // Gets set of vars modified by procName
    virtual std::unordered_set<std::string> getVarsByProc(const std::string& procName) = 0;
    // Gets set of procs that modify varName
    virtual std::unordered_set<std::string> getProcsByVar(const std::string& varName) = 0;
    // Gets set of vars that are modified by some procs
    virtual std::unordered_set<std::string> getVarsInProcs() = 0;
    // Gets set of procs that modifies some var
    virtual std::unordered_set<std::string> getProcs() = 0;
    // Checks if procName modifies varName
    virtual bool isAssociatedP(const std::string& procName, const std::string& varName) = 0;
    // Checks if there contains at least one modifies P
    virtual bool hasAssociatedP() = 0;
    // Checks if procName is modifies P
    virtual bool hasAssociatedPByKey(const std::string& procName) = 0;
    // Checks if varName is modifies P
    virtual bool hasAssociatedPByValue(const std::string& varName) = 0;
};
