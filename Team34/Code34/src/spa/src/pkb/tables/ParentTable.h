// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once

#include <unordered_map>
#include <unordered_set>
#include "pkb/base/BaseMapSet.h"
#include "pkb/base/BaseMap.h"
#include "FollowsParentTable.h"

class ParentTable : public FollowsParentTable {
private:
    BaseMapSet<int, int> keyToValEntries;   // <stmt_num, set_of_children_stmts>
    BaseMap<int, int> valToKeyEntries;      // <stmt_num, parent_stmt>

public:
    // ---------- Parent ----------
    std::unordered_map<int, std::unordered_set<int>> getParentEntries() override;
    std::unordered_set<int> getParents() override;
    std::unordered_set<int> getChildren() override;
    std::unordered_set<int> getChildrenOf(const int& parentStmt) override;
    int getParentOf(const int& childStmt) override;
    bool isAssociated(const int& keyStmt, const int& valStmt) override;
    bool hasAssociated() override;
    bool hasAssociatedByKey(const int& keyStmt) override;
    bool hasAssociatedByValue(const int& valStmt) override;
    void addRelation(const int& keyStmt, const int& valStmt) override;
};
