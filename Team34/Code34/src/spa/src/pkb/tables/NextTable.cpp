// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "NextTable.h"
#include "common/CollectionUtils.h"

void NextTable::clearNextT() {
    computedAll = false;
    keyToValTEntries = BaseMapSet<int, int>();
    valToKeyTEntries = BaseMapSet<int, int>();
}

void NextTable::addNext(const int& front, const int& back) {
    this->keyToValEntries.addEntry(front, back);
    this->valToKeyEntries.addEntry(back, front);
}

std::unordered_map<int, std::unordered_set<int>> NextTable::getNextEntries() {
    return this->keyToValEntries.getEntries();
}

std::unordered_map<int, std::unordered_set<int>> NextTable::getNextTEntries() {
    if (computedAll)
        return keyToValTEntries.getEntries();
    for (auto& key : keyToValEntries.getKeys()) {
        generateT(key, keyToValEntries, keyToValTEntries);
    }
    computedAll = true;
    return keyToValTEntries.getEntries();
}

bool NextTable::isNext(const int& key, const int& value) {
    return this->keyToValEntries.hasKey(key) &&
        this->keyToValEntries.getValuesByKey(key).count(value) > 0;
}

bool NextTable::isNextT(const int& key, const int& value) {
    generateT(key, keyToValEntries, keyToValTEntries);
    return this->keyToValTEntries.hasKey(key) &&
        this->keyToValTEntries.getValuesByKey(key).count(value) > 0;
}

std::unordered_set<int> NextTable::getKeysByValue(const int& value) {
    if (this->valToKeyEntries.hasKey(value)) {
        return this->valToKeyEntries.getValuesByKey(value);
    }
    std::unordered_set<int> emptySet;
    return emptySet;
}

std::unordered_set<int> NextTable::getValuesByKey(const int& key) {
    if (this->keyToValEntries.hasKey(key)) {
        return this->keyToValEntries.getValuesByKey(key);
    }
    std::unordered_set<int> emptySet;
    return emptySet;
}

std::unordered_set<int> NextTable::getTKeysByValue(const int& value) {
    generateT(value, valToKeyEntries, valToKeyTEntries);
    if (this->valToKeyTEntries.hasKey(value)) {
        return this->valToKeyTEntries.getValuesByKey(value);
    }
    std::unordered_set<int> emptySet;
    return emptySet;
}

std::unordered_set<int> NextTable::getTValuesByKey(const int& key) {
    generateT(key, keyToValEntries, keyToValTEntries);
    if (this->keyToValTEntries.hasKey(key)) {
        return this->keyToValTEntries.getValuesByKey(key);
    }
    std::unordered_set<int> emptySet;
    return emptySet;
}

bool NextTable::hasNext() {
    return this->keyToValEntries.getSize() > 0;
}

bool NextTable::hasNextByKey(const int& key) {
    return !this->keyToValEntries.getValuesByKey(key).empty();
}

bool NextTable::hasNextByValue(const int& value) {
    return !this->valToKeyEntries.getValuesByKey(value).empty();
}
