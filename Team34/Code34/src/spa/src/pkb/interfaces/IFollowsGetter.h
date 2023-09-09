// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
#include "di/IService.h"

class IFollowsGetter : public virtual IService {
public:
    ~IFollowsGetter() override = default;

    // ---------- Follows ----------

    // Gets all follows entries
    virtual std::unordered_map<int, int> getFollowsEntries() = 0;
    // Gets all before stmts
    virtual std::unordered_set<int> getBeforeStmts() = 0;
    // Gets all after stmts
    virtual std::unordered_set<int> getAfterStmts() = 0;
    // Gets stmt directly after stmtNum
    virtual int getStmtAfter(const int& stmtNum) = 0;
    // Gets stmt directly before stmtNum
    virtual int getStmtBefore(const int& stmtNum) = 0;
    // Checks if afterStmt appears directly after beforeStmt
    virtual bool isAssociated(const int& keyStmt, const int& valStmt) = 0;
    // Checks if there exists follows stmt
    virtual bool hasAssociated() = 0;
    // Checks if beforeStmt is follows
    virtual bool hasAssociatedByKey(const int& keyStmt) = 0;
    // Checks if afterStmt is follows
    virtual bool hasAssociatedByValue(const int& valStmt) = 0;


    // ---------- FollowsT ----------

    // Gets all followsT entries
    virtual std::unordered_map<int, std::unordered_set<int>> getTEntries() = 0;
    // Gets all stmts after stmtNum
    virtual std::unordered_set<int> getTStmtsByKey(const int& keyStmt) = 0;
    // Gets all stmts before stmtNum
    virtual std::unordered_set<int> getTStmtsByValue(const int& valStmt) = 0;
    // Checks if afterStmt appears after beforeStmt
    virtual bool isAssociatedT(const int& keyStmt, const int& valStmt) = 0;
    // Checks if there exists followsT stmt
    virtual bool hasAssociatedT() = 0;
    // Checks if beforeStmt is followsT
    virtual bool hasAssociatedTByKey(const int &keyStmt) = 0;
    // Checks if afterStmt is followsT
    virtual bool hasAssociatedTByValue(const int &valStmt) = 0;
};
