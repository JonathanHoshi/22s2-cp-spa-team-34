// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once

#include <unordered_map>
#include <unordered_set>
#include "pkb/base/BaseMap.h"
#include "FollowsParentTable.h"

class FollowsTable : public FollowsParentTable {
private:
    BaseMap<int, int> keyToValEntries;       // <key_stmt, val_stmt>
    BaseMap<int, int> valToKeyEntries;       // <val_stmt, key_stmt>

public:
    // ---------- Follows ----------

    std::unordered_map<int, int> getFollowsEntries() override;
    std::unordered_set<int> getBeforeStmts() override;
    std::unordered_set<int> getAfterStmts() override;
    int getStmtAfter(const int& stmtNum) override;
    int getStmtBefore(const int& stmtNum) override;
    bool isAssociated(const int& keyStmt, const int& valStmt) override;
    bool hasAssociated() override;
    bool hasAssociatedByKey(const int& keyStmt) override;
    bool hasAssociatedByValue(const int& valStmt) override;
    void addRelation(const int& keyStmt, const int& valStmt) override;
};
