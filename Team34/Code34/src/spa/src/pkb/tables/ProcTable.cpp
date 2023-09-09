// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "ProcTable.h"

std::unordered_set<std::string> ProcTable::getProcs() {
    return procList.getEntries();
}

void ProcTable::addProc(const std::string& procStr) {
    procList.addEntry(procStr);
}

void ProcTable::addProcs(const std::unordered_set<std::string>& procSet) {
    for (const auto& item : procSet) {
        procList.addEntry(item);
    }
}

bool ProcTable::isProc(const std::string& procStr) {
    return procList.containKey(procStr);
}

size_t ProcTable::getSize() {
    return procList.getSize();
}
