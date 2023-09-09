// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
#include "di/IService.h"

class ICallsGetter : public virtual IService {
public:
    ~ICallsGetter() override = default;

    // ---------- Calls ----------
    virtual std::unordered_map<std::string, std::unordered_set<std::string>>
        getCallsEntries() = 0;  // Gets all calls entries
    virtual std::unordered_set<std::string>
        getCallerProcs() = 0;  // Gets all procs that call some proc
    virtual std::unordered_set<std::string>
        getCalleeProcs() = 0;  // Gets all procs that are called by some proc
    virtual std::unordered_set<std::string> getProcsCalledBy(
        const std::string& callerProc) = 0;  // Gets all procs called by the caller proc
    virtual std::unordered_set<std::string> getProcsCalling(
        const std::string& calleeProc) = 0;  // Gets all procs calling the callee proc
    virtual bool isCalls(
        const std::string& callerProc,
        const std::string& calleeProc) = 0;  // Checks if callerProc calls calleeProc
    virtual bool hasCalls() = 0;             // Checks if there exists calls stmt
    virtual bool
        hasCallsByKey(const std::string& callerProc) = 0;  // Checks if callerProc calls
    virtual bool hasCallsByValue(
        const std::string& calleeProc) = 0;  // Checks if calleeProc is called

    // ---------- CallsT ----------
    virtual std::unordered_map<std::string, std::unordered_set<std::string>>
        getCallsTEntries() = 0;  // Gets all callsT entries
    virtual std::unordered_set<std::string> getProcsCalledTBy(
        const std::string
        & callerProc) = 0;  // Gets all procs calledT by the caller proc
    virtual std::unordered_set<std::string> getProcsCallingT(
        const std::string& calleeProc) = 0;  // Gets all procs callingT the callee proc
    virtual bool isCallsT(
        const std::string& callerProc,
        const std::string& calleeProc) = 0;  // Checks if callerProc callsT calleeProc
    virtual bool hasCallsT() = 0;            // Checks if there exists callsT stmt
    virtual bool
        hasCallsTByKey(const std::string& callerProc) = 0;  // Checks if callerProc callsT
    virtual bool hasCallsTByValue(
        const std::string& calleeProc) = 0;  // Checks if calleeProc is calledT
};
