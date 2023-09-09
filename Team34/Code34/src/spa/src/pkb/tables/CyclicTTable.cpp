// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "CyclicTTable.h"

void CyclicTTable::generateT(const int& key, BaseMapSet<int, int>& direction,
    BaseMapSet<int, int>& directionT) {
    if (!direction.hasKey(key) || directionT.hasKey(key)) {
        return;
    }
    std::queue<int> valueQueue;
    for (int i : direction.getValuesByKey(key)) {
        valueQueue.push(i);
    }
    while (!valueQueue.empty()) {
        int curVal = valueQueue.front();
        valueQueue.pop();
        if (directionT.hasKeyValue(key, curVal)) {
            continue;
        }
        directionT.addEntry(key, curVal);
        for (int i : direction.getValuesByKey(curVal)) {
            valueQueue.push(i);
        }
    }
}
