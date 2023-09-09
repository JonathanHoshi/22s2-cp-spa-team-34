// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "FollowsParentTable.h"

// ---------- RelationT ----------

std::unordered_map<int, std::unordered_set<int>> FollowsParentTable::getTEntries() {
    return this->keyToValTEntries.getEntries();
}

std::unordered_set<int> FollowsParentTable::getTStmtsByKey(const int &keyStmt) {
    return this->keyToValTEntries.getValuesByKey(keyStmt);
}

std::unordered_set<int> FollowsParentTable::getTStmtsByValue(const int& valStmt) {
    return this->valToKeyTEntries.getValuesByKey(valStmt);
}

bool FollowsParentTable::isAssociatedT(const int& keyStmt, const int& valStmt) {
    return this->keyToValTEntries.hasKeyValue(keyStmt, valStmt);
}

bool FollowsParentTable::hasAssociatedT() {
    return this->keyToValTEntries.getSize() > 0;
}

bool FollowsParentTable::hasAssociatedTByKey(const int &keyStmt) {
    return this->keyToValTEntries.hasKey(keyStmt);
}

bool FollowsParentTable::hasAssociatedTByValue(const int &valStmt) {
    return this->valToKeyTEntries.hasKey(valStmt);
}

void FollowsParentTable::addRelationT(const int &keyStmt, const int &valStmt) {
    this->keyToValTEntries.addEntry(keyStmt, valStmt);
    this->valToKeyTEntries.addEntry(valStmt, keyStmt);
}

// Virtual methods to be implemented by FollowsTable and ParentTable

std::unordered_map<int, int> FollowsParentTable::getFollowsEntries() {
    throw std::logic_error("Not implemented");
}

std::unordered_set<int> FollowsParentTable::getBeforeStmts() {
    throw std::logic_error("Not implemented");
}

std::unordered_set<int> FollowsParentTable::getAfterStmts() {
    throw std::logic_error("Not implemented");
}

int FollowsParentTable::getStmtAfter(const int &stmtNum) {
    throw std::logic_error("Not implemented");
}

int FollowsParentTable::getStmtBefore(const int &stmtNum) {
    throw std::logic_error("Not implemented");
}

std::unordered_map<int, std::unordered_set<int>> FollowsParentTable::getParentEntries() {
    throw std::logic_error("Not implemented");
}

std::unordered_set<int> FollowsParentTable::getParents() {
    throw std::logic_error("Not implemented");
}

std::unordered_set<int> FollowsParentTable::getChildren() {
    throw std::logic_error("Not implemented");
}

std::unordered_set<int> FollowsParentTable::getChildrenOf(const int &parentStmt) {
    throw std::logic_error("Not implemented");
}

int FollowsParentTable::getParentOf(const int &childStmt) {
    throw std::logic_error("Not implemented");
}


