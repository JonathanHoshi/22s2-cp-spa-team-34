// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "VarTable.h"

std::unordered_set<std::string> VarTable::getVars() {
    return varList.getEntries();
}

void VarTable::addVar(const std::string& varStr) {
    varList.addEntry(varStr);
}

void VarTable::addVars(const std::unordered_set<std::string>& varSet) {
    for (const auto& item : varSet) {
        varList.addEntry(item);
    }
}

bool VarTable::isVar(const std::string& varStr) {
    return varList.containKey(varStr);
}

size_t VarTable::getSize() {
    return varList.getSize();
}
