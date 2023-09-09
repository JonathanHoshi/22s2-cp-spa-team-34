// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once

#include <unordered_map>
#include <unordered_set>
#include <string>
#include "pkb/base/BaseMapSet.h"
#include "pkb/interfaces/ICallsAdder.h"
#include "pkb/interfaces/ICallsGetter.h"

class CallsTable : public ICallsAdder, public ICallsGetter {
private:
    // <caller_proc, callee_proc>
    BaseMapSet<std::string, std::string> callerToCalleeEntries;
    // <callee_proc, caller_proc>
    BaseMapSet<std::string, std::string> calleeToCallerEntries;
    // <caller_proc, callee_proc> transitive
    BaseMapSet<std::string, std::string> callerToCalleeTEntries;
    // <callee_proc, caller_proc> transitive
    BaseMapSet<std::string, std::string> calleeToCallerTEntries;

public:
    // ---------- Calls ----------
    std::unordered_map<std::string, std::unordered_set<std::string>> getCallsEntries() override;
    std::unordered_set<std::string> getCallerProcs() override;
    std::unordered_set<std::string> getCalleeProcs() override;
    std::unordered_set<std::string> getProcsCalledBy(const std::string& callerProc) override;
    std::unordered_set<std::string> getProcsCalling(const std::string& calleeProc) override;
    bool isCalls(const std::string& callerProc, const std::string& calleeProc) override;
    bool hasCalls() override;
    bool hasCallsByKey(const std::string& callerProc) override;
    bool hasCallsByValue(const std::string& calleeProc) override;
    void addCalls(const std::string& callerProc, const std::string& calleeProc) override;

    // ---------- CallsT ----------
    std::unordered_map<std::string, std::unordered_set<std::string>> getCallsTEntries() override;
    std::unordered_set<std::string> getProcsCalledTBy(const std::string& callerProc) override;
    std::unordered_set<std::string> getProcsCallingT(const std::string& calleeProc) override;
    bool isCallsT(const std::string& callerProc, const std::string& calleeProc) override;
    bool hasCallsT() override;
    bool hasCallsTByKey(const std::string& callerProc) override;
    bool hasCallsTByValue(const std::string& calleeProc) override;
    void addCallsT(const std::string& callerProc, const std::string& calleeProc) override;
};
