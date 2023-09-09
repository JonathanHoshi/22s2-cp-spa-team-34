// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once

#include <unordered_map>
#include <unordered_set>
#include "di/IService.h"

class IParentGetter : public virtual IService {
public:
    ~IParentGetter() override = default;

    // ---------- Parent ----------

    // Gets all parent entries
    virtual std::unordered_map<int, std::unordered_set<int>> getParentEntries() = 0;
    // Gets all stmts that are parents
    virtual std::unordered_set<int> getParents() = 0;
    // Gets all stmts that are children
    virtual std::unordered_set<int> getChildren() = 0;
    // Gets all direct children of parentStmt
    virtual std::unordered_set<int> getChildrenOf(const int& parentStmt) = 0;
    // Gets parent of childStmt
    virtual int getParentOf(const int& childStmt) = 0;
    // Checks if parentStmt is parent of childStmt
    virtual bool isAssociated(const int& keyStmt, const int& valStmt) = 0;
    // Checks if there exists parent stmt
    virtual bool hasAssociated() = 0;
    // Checks if parentStmt is parent
    virtual bool hasAssociatedByKey(const int& keyStmt) = 0;
    // Checks if childStmt is parent
    virtual bool hasAssociatedByValue(const int& valStmt) = 0;

    // ---------- ParentT ----------

    // Gets all parentT entries
    virtual std::unordered_map<int, std::unordered_set<int>> getTEntries() = 0;
    // Gets all descendants of parentStmt
    virtual std::unordered_set<int> getTStmtsByKey(const int& keyStmt) = 0;
    // Gets all ancestors of childStmt
    virtual std::unordered_set<int> getTStmtsByValue(const int& valStmt) = 0;
    // Checks if parentStmt is ancestor of childStmt
    virtual bool isAssociatedT(const int& keyStmt, const int& valStmt) = 0;
    // Checks if there exists parentT stmt
    virtual bool hasAssociatedT() = 0;
    // Checks if parentStmt is parentT
    virtual bool hasAssociatedTByKey(const int &keyStmt) = 0;
    // Checks if childStmt is parentT
    virtual bool hasAssociatedTByValue(const int &valStmt) = 0;
};
