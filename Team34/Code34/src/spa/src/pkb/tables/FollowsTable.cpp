// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "FollowsTable.h"

// ---------- Follows ----------

std::unordered_map<int, int> FollowsTable::getFollowsEntries() {
    return this->keyToValEntries.getEntries();
}

std::unordered_set<int> FollowsTable::getBeforeStmts() {
    return this->keyToValEntries.getKeys();
}

std::unordered_set<int> FollowsTable::getAfterStmts() {
    return this->valToKeyEntries.getKeys();
}

int FollowsTable::getStmtAfter(const int& stmtNum) {
    return this->keyToValEntries.getValueByKey(stmtNum);
}

int FollowsTable::getStmtBefore(const int& stmtNum) {
    return this->valToKeyEntries.getValueByKey(stmtNum);
}

bool FollowsTable::isAssociated(const int& keyStmt, const int& valStmt) {
    return this->keyToValEntries.hasKeyValue(keyStmt, valStmt);
}

bool FollowsTable::hasAssociated() {
    return this->keyToValEntries.getSize() > 0;
}

bool FollowsTable::hasAssociatedByKey(const int& keyStmt) {
    return this->keyToValEntries.hasKey(keyStmt);
}

bool FollowsTable::hasAssociatedByValue(const int& valStmt) {
    return this->valToKeyEntries.hasKey(valStmt);
}

void FollowsTable::addRelation(const int& keyStmt, const int& valStmt) {
    this->keyToValEntries.addEntry(keyStmt, valStmt);
    this->valToKeyEntries.addEntry(valStmt, keyStmt);
}
