// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once
#include <string>
#include <unordered_map>
#include <unordered_set>
#include "di/IService.h"

class IUsesGetter : public virtual IService {
public:
    ~IUsesGetter() override = default;

    // ---------- Uses: Statements ----------
    // Gets all stmt-uses-var entries
    virtual std::unordered_map<int, std::unordered_set<std::string>> getStmtVarEntries() = 0;
    // Gets var used by stmtNum
    virtual std::unordered_set<std::string> getVarsByStmt(const int& stmtNum) = 0;
    // Gets set of stmts that uses varName
    virtual std::unordered_set<int> getStmtsByVar(const std::string& varName) = 0;
    // Gets set of vars that are used by some stmt
    virtual std::unordered_set<std::string> getVarsInStmts() = 0;
    // Gets set of stmts that uses some var
    virtual std::unordered_set<int> getStmts() = 0;
    // Checks if stmtNum uses varName
    virtual bool isAssociatedS(const int& stmtNum, const std::string& varName) = 0;
    // Checks if there exists uses S
    virtual bool hasAssociatedS() = 0;
    // Checks if stmtNum is uses S
    virtual bool hasAssociatedSByKey(const int& stmtNum) = 0;
    // Checks if varName is uses S
    virtual bool hasAssociatedSByValue(const std::string& varName) = 0;

    // ---------- Uses: Procedures ----------
    // Gets all proc-uses-var entries
    virtual std::unordered_map<std::string,
        std::unordered_set<std::string>> getProcVarEntries() = 0;
    // Gets set of vars used by procName
    virtual std::unordered_set<std::string> getVarsByProc(const std::string& procName) = 0;
    // Gets set of procs that uses varName
    virtual std::unordered_set<std::string> getProcsByVar(const std::string& varName) = 0;
    // Gets set of vars that are used by some proc
    virtual std::unordered_set<std::string> getVarsInProcs() = 0;
    // Gets set of procs that uses some var
    virtual std::unordered_set<std::string> getProcs() = 0;
    // Checks if procName uses varName
    virtual bool isAssociatedP(const std::string& procName, const std::string& varName) = 0;
    // Checks if there exists uses P
    virtual bool hasAssociatedP() = 0;
    // Checks if procName is uses P
    virtual bool hasAssociatedPByKey(const std::string& procName) = 0;
    // Checks if varName is uses P
    virtual bool hasAssociatedPByValue(const std::string& varName) = 0;
};
