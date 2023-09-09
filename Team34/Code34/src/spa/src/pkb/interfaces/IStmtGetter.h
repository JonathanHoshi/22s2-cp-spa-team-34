// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once

#include <string>
#include <unordered_set>
#include <unordered_map>
#include "di/IService.h"

class IStmtGetter : public virtual IService {
public:
    ~IStmtGetter() override = default;

    virtual std::unordered_set<int> getAllStmts() = 0;
    virtual std::unordered_set<int> getReadStmts() = 0;
    virtual std::unordered_set<int> getPrintStmts() = 0;
    virtual std::unordered_set<int> getAssignStmts() = 0;
    virtual std::unordered_set<int> getCallStmts() = 0;
    virtual std::unordered_set<int> getWhileStmts() = 0;
    virtual std::unordered_set<int> getIfStmts() = 0;

    virtual bool isReadStmt(const int& stmtNum) = 0;
    virtual bool isPrintStmt(const int& stmtNum) = 0;
    virtual bool isAssignStmt(const int& stmtNum) = 0;
    virtual bool isCallStmt(const int& stmtNum) = 0;
    virtual bool isWhileStmt(const int& stmtNum) = 0;
    virtual bool isIfStmt(const int& stmtNum) = 0;

    virtual std::unordered_map<int, std::string> getCallProcEntries() = 0;
    virtual std::unordered_map<int, std::string> getPrintVarEntries() = 0;
    virtual std::unordered_map<int, std::string> getReadVarEntries() = 0;
    virtual std::string getCallProc(const int& stmtNum) = 0;
    virtual std::string getPrintVar(const int& stmtNum) = 0;
    virtual std::string getReadVar(const int& stmtNum) = 0;
};
