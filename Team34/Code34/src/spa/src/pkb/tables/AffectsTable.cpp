// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "AffectsTable.h"

void AffectsTable::generateAffected(const int& value) {
    if (!stmtGetter->isAssignStmt(value) || computedAffected.count(value) > 0) {
        return;
    }
    computedAffected.insert(value);
    for (auto& stmt : nextGetter->getTKeysByValue(value)) {
        generateAffects(stmt);
    }
}

void AffectsTable::generateAffects(const int& key) {
    if (!stmtGetter->isAssignStmt(key) || computedAffects.count(key) > 0) {
        return;
    }
    computedAffects.insert(key);
    std::string modifiedVariable = *(modifiesGetter->getVarsByStmt(key).begin());
    std::queue<int> valueQueue;
    std::unordered_set<int> visited;
    for (int i : nextGetter->getValuesByKey(key)) {
        valueQueue.push(i);
    }
    while (!valueQueue.empty()) {
        int currStmt = valueQueue.front();
        valueQueue.pop();
        if (visited.count(currStmt) > 0) {
            continue;
        }
        visited.insert(currStmt);
        bool cont = handleAffects(key, currStmt, modifiedVariable);
        if (keyToValEntries.hasKeyValue(key, currStmt)) {
            generateAffects(currStmt);
        }
        if (!cont) {
            continue;
        }
        for (int i : nextGetter->getValuesByKey(currStmt)) {
            valueQueue.push(i);
        }
    }
}

bool AffectsTable::handleAffects(const int& key, const int& value, const std::string& var) {
    if (parentGetter->hasAssociatedByKey(value)) {
        return true;
    }
    if (stmtGetter->isAssignStmt(value) &&
        usesGetter->getVarsByStmt(value).count(var) > 0) {
        keyToValEntries.addEntry(key, value);
        valToKeyEntries.addEntry(value, key);
    }
    auto set = modifiesGetter->getVarsByStmt(value);
    return set.count(var) == 0;
}

AffectsTable::AffectsTable(IModifiesGetter& modifiesGetter, IUsesGetter& usesGetter,
    INextGetter& nextGetter, IParentGetter& parentGetter, IStmtGetter& stmtGetter) {
    this->modifiesGetter = &modifiesGetter;
    this->usesGetter = &usesGetter;
    this->nextGetter = &nextGetter;
    this->parentGetter = &parentGetter;
    this->stmtGetter = &stmtGetter;
}

bool AffectsTable::isAffects(const int& keyStmt, const int& affectedStmt) {
    generateAffects(keyStmt);
    return keyToValEntries.hasKeyValue(keyStmt, affectedStmt);
}

bool AffectsTable::isAffectsT(const int& keyStmt, const int& affectedStmt) {
    generateAffects(keyStmt);
    generateT(keyStmt, keyToValEntries, keyToValTEntries);
    return keyToValTEntries.hasKeyValue(keyStmt, affectedStmt);
}

bool AffectsTable::hasAffects() {
    for (auto& stmt : stmtGetter->getAssignStmts()) {
        if (hasAffectsByKeyStmt(stmt)) {
            return true;
        }
    }
    return false;
}

bool AffectsTable::hasAffectsByKeyStmt(const int& keyStmt) {
    generateAffects(keyStmt);
    return keyToValEntries.hasKey(keyStmt);
}

std::unordered_map<int, std::unordered_set<int>> AffectsTable::getAffectsEntries() {
    if (computedAffects.size() ==
        stmtGetter->getAssignStmts().size())
        return keyToValEntries.getEntries();

    for (auto& stmt : stmtGetter->getAssignStmts()) {
        generateAffects(stmt);
    }
    return keyToValEntries.getEntries();
}

std::unordered_map<int, std::unordered_set<int>> AffectsTable::getAffectsTEntries() {
    if (computedAffectsT)
        return keyToValTEntries.getEntries();
    for (auto& stmt : stmtGetter->getAssignStmts()) {
        generateAffects(stmt);
        generateT(stmt, keyToValEntries, keyToValTEntries);
    }
    computedAffectsT = true;
    return keyToValTEntries.getEntries();
}

bool AffectsTable::hasAffectsByAffectedStmt(const int& affectedStmt) {
    generateAffected(affectedStmt);
    return valToKeyEntries.hasKey(affectedStmt);
}

std::unordered_set<int> AffectsTable::getKeyStmtsByAffectedStmt(const int& affectedStmt) {
    generateAffected(affectedStmt);
    return valToKeyEntries.getValuesByKey(affectedStmt);
}

std::unordered_set<int> AffectsTable::getTKeyStmtsByAffectedStmt(const int& affectedStmt) {
    generateAffected(affectedStmt);
    generateT(affectedStmt, valToKeyEntries, valToKeyTEntries);
    return valToKeyTEntries.getValuesByKey(affectedStmt);
}

std::unordered_set<int> AffectsTable::getAffectedStmtsByKeyStmt(const int& keyStmt) {
    generateAffects(keyStmt);
    return keyToValEntries.getValuesByKey(keyStmt);
}

std::unordered_set<int> AffectsTable::getTAffectedStmtsByKeyStmt(const int& keyStmt) {
    generateAffects(keyStmt);
    generateT(keyStmt, keyToValEntries, keyToValTEntries);
    return keyToValTEntries.getValuesByKey(keyStmt);
}

void AffectsTable::clearAffectsAndT() {
    keyToValEntries = BaseMapSet<int, int>();
    valToKeyEntries = BaseMapSet<int, int>();
    keyToValTEntries = BaseMapSet<int, int>();
    valToKeyTEntries = BaseMapSet<int, int>();
    computedAffects = std::unordered_set<int>();
    computedAffected = std::unordered_set<int>();
    computedAffectsT = false;
}
