// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "ParentTable.h"

// ---------- Parent ----------

std::unordered_map<int, std::unordered_set<int>> ParentTable::getParentEntries() {
    return this->keyToValEntries.getEntries();
}

std::unordered_set<int> ParentTable::getParents() {
    return this->keyToValEntries.getKeys();
}

std::unordered_set<int> ParentTable::getChildren() {
    return this->valToKeyEntries.getKeys();
}

std::unordered_set<int> ParentTable::getChildrenOf(const int& parentStmt) {
    return this->keyToValEntries.getValuesByKey(parentStmt);
}

int ParentTable::getParentOf(const int& childStmt) {
    return this->valToKeyEntries.getValueByKey(childStmt);
}

bool ParentTable::isAssociated(const int& parentStmt, const int& childStmt) {
    return this->keyToValEntries.hasKeyValue(parentStmt, childStmt);
}

bool ParentTable::hasAssociated() {
    return this->keyToValEntries.getSize() > 0;
}

bool ParentTable::hasAssociatedByKey(const int& keyStmt) {
    return this->keyToValEntries.hasKey(keyStmt);
}

bool ParentTable::hasAssociatedByValue(const int& valStmt) {
    return this->valToKeyEntries.hasKey(valStmt);
}

void ParentTable::addRelation(const int& keyStmt, const int& valStmt) {
    this->keyToValEntries.addEntry(keyStmt, valStmt);
    this->valToKeyEntries.addEntry(valStmt, keyStmt);
}
