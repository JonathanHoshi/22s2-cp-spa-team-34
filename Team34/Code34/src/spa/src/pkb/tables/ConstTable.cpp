// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "ConstTable.h"

std::unordered_set<int> ConstTable::getConsts() {
    return constList.getEntries();
}

void ConstTable::addConst(const int& constVal) {
    constList.addEntry(constVal);
}

void ConstTable::addConsts(const std::unordered_set<int>& constSet) {
    for (const auto& item : constSet) {
        constList.addEntry(item);
    }
}

bool ConstTable::isConst(const int& constVal) {
    return constList.containKey(constVal);
}

size_t ConstTable::getSize() {
    return constList.getSize();
}
