// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "CallsTable.h"

// ---------- Calls ----------
std::unordered_map<std::string, std::unordered_set<std::string>> CallsTable::getCallsEntries() {
    return this->callerToCalleeEntries.getEntries();
}

std::unordered_set<std::string> CallsTable::getCallerProcs() {
    return this->callerToCalleeEntries.getKeys();
}

std::unordered_set<std::string> CallsTable::getCalleeProcs() {
    return this->calleeToCallerEntries.getKeys();
}

std::unordered_set<std::string> CallsTable::getProcsCalledBy(const std::string& callerProc) {
    return this->callerToCalleeEntries.getValuesByKey(callerProc);
}

std::unordered_set<std::string> CallsTable::getProcsCalling(const std::string& calleeProc) {
    return this->calleeToCallerEntries.getValuesByKey(calleeProc);
}

bool CallsTable::isCalls(const std::string& callerProc, const std::string& calleeProc) {
    return this->callerToCalleeEntries.hasKeyValue(callerProc, calleeProc);
}

bool CallsTable::hasCalls() {
    return this->callerToCalleeEntries.getSize() > 0;
}

bool CallsTable::hasCallsByKey(const std::string& callerProc) {
    return this->callerToCalleeEntries.hasKey(callerProc);
}

bool CallsTable::hasCallsByValue(const std::string& calleeProc) {
    return this->calleeToCallerEntries.hasKey(calleeProc);
}

void CallsTable::addCalls(const std::string& callerProc, const std::string& calleeProc) {
    this->callerToCalleeEntries.addEntry(callerProc, calleeProc);
    this->calleeToCallerEntries.addEntry(calleeProc, callerProc);
}

// ---------- CallsT ----------
std::unordered_map<std::string, std::unordered_set<std::string>> CallsTable::getCallsTEntries() {
    return this->callerToCalleeTEntries.getEntries();
}

std::unordered_set<std::string> CallsTable::getProcsCalledTBy(const std::string& callerProc) {
    return this->callerToCalleeTEntries.getValuesByKey(callerProc);
}

std::unordered_set<std::string> CallsTable::getProcsCallingT(const std::string& calleeProc) {
    return this->calleeToCallerTEntries.getValuesByKey(calleeProc);
}

bool CallsTable::isCallsT(const std::string& callerProc, const std::string& calleeProc) {
    return this->callerToCalleeTEntries.hasKeyValue(callerProc, calleeProc);
}

bool CallsTable::hasCallsT() {
    return this->callerToCalleeTEntries.getSize() > 0;
}

bool CallsTable::hasCallsTByKey(const std::string& callerProc) {
    return this->callerToCalleeTEntries.hasKey(callerProc);
}

bool CallsTable::hasCallsTByValue(const std::string& calleeProc) {
    return this->calleeToCallerTEntries.hasKey(calleeProc);
}

void CallsTable::addCallsT(const std::string& callerProc, const std::string& calleeProc) {
    this->callerToCalleeTEntries.addEntry(callerProc, calleeProc);
    this->calleeToCallerTEntries.addEntry(calleeProc, callerProc);
}
