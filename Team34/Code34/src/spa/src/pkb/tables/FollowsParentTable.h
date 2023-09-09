// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once

#include <unordered_map>
#include <unordered_set>
#include <stdexcept>
#include "pkb/base/BaseMap.h"
#include "pkb/base/BaseMapSet.h"
#include "pkb/interfaces/IFollowsAdder.h"
#include "pkb/interfaces/IFollowsGetter.h"
#include "pkb/interfaces/IParentAdder.h"
#include "pkb/interfaces/IParentGetter.h"

class FollowsParentTable : public IFollowsAdder, public IFollowsGetter,
                           public IParentAdder, public IParentGetter {
protected:
    BaseMapSet<int, int> keyToValTEntries;   // <keyT_stmt, valT_stmt>
    BaseMapSet<int, int> valToKeyTEntries;   // <keyT_stmt, valT_stmt>

public:
    // ---------- RelationT ----------
    std::unordered_map<int, std::unordered_set<int>> getTEntries() override;
    std::unordered_set<int> getTStmtsByKey(const int& stmtNum) override;
    std::unordered_set<int> getTStmtsByValue(const int& stmtNum) override;
    bool isAssociatedT(const int& keyStmt, const int& valStmt) override;
    bool hasAssociatedT() override;
    bool hasAssociatedTByKey(const int& keyStmt) override;
    bool hasAssociatedTByValue(const int& valStmt) override;
    void addRelationT(const int& keyStmt, const int& valStmt) override;

    // Virtual methods to be implemented by FollowsTable and ParentTable
    std::unordered_map<int, int> getFollowsEntries() override;
    std::unordered_set<int> getBeforeStmts() override;
    std::unordered_set<int> getAfterStmts() override;
    int getStmtAfter(const int& stmtNum) override;
    int getStmtBefore(const int& stmtNum) override;
    std::unordered_map<int, std::unordered_set<int>> getParentEntries() override;
    std::unordered_set<int> getParents() override;
    std::unordered_set<int> getChildren() override;
    std::unordered_set<int> getChildrenOf(const int& parentStmt) override;
    int getParentOf(const int& childStmt) override;
};
