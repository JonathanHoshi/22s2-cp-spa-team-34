// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once
#include <string>
#include <unordered_set>
#include <unordered_map>
#include "di/IService.h"

class IStmtAdder : public virtual IService {
public:
    ~IStmtAdder() override = default;

    virtual void addReadStmt(const int& stmtNum, const std::string& varName) = 0;
    virtual void addPrintStmt(const int& stmtNum, const std::string& varName) = 0;
    virtual void addAssignStmt(const int& stmtNum) = 0;
    virtual void addCallStmt(const int& stmtNum, const std::string& procName) = 0;
    virtual void addWhileStmt(const int& stmtNum) = 0;
    virtual void addIfStmt(const int& stmtNum) = 0;

    virtual void addReadStmts(const std::unordered_map<int, std::string>& stmtSet) = 0;
    virtual void addPrintStmts(const std::unordered_map<int, std::string>& stmtSet) = 0;
    virtual void addAssignStmts(const std::unordered_set<int>& stmtSet) = 0;
    virtual void addCallStmts(const std::unordered_map<int, std::string>& stmtSet) = 0;
    virtual void addWhileStmts(const std::unordered_set<int>& stmtSet) = 0;
    virtual void addIfStmts(const std::unordered_set<int>& stmtSet) = 0;
};
