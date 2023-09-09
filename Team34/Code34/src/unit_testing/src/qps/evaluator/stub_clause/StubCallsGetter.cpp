#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "common/CollectionUtils.h"
#include "pkb/interfaces/ICallsGetter.h"



class StubCallsGetter : public ICallsGetter
{
private:
    std::unordered_map<std::string, std::unordered_set<std::string>> callsEntries;
    std::unordered_map<std::string, std::unordered_set<std::string>> reverseCallEntries;

    std::unordered_map<std::string, std::unordered_set<std::string>> callsTEntries;
    std::unordered_map<std::string, std::unordered_set<std::string>> reverseCallTEntries;

public:
    void setCallsEntries(std::unordered_map<std::string, std::unordered_set<std::string>> callsEntries) 
    {
        this->callsEntries = callsEntries;

        // handle reverseCallsEntries
        for (auto& [key, valueSet] : callsEntries)
        {
            for (auto& value : valueSet)
            {
                CollectionUtils::insert(reverseCallEntries, value, key);
            }
        }
    }

    void setCallsTEntries(std::unordered_map<std::string, std::unordered_set<std::string>> callsTEntries)
    {
        this->callsTEntries = callsTEntries;

        // handle reverseCallsEntries
        for (auto& [key, valueSet] : callsTEntries)
        {
            for (auto& value : valueSet)
            {
                CollectionUtils::insert(reverseCallTEntries, value, key);
            }
        }
    }

    virtual std::unordered_map<std::string, std::unordered_set<std::string>> getCallsEntries() override
    {
        return this->callsEntries;
    }

    virtual std::unordered_set<std::string> getCallerProcs() override
    {
        std::unordered_set<std::string> result;
        CollectionUtils::collapseKey(callsEntries, result);
        return result;
    }

    virtual std::unordered_set<std::string> getCalleeProcs() override
    {
        std::unordered_set<std::string> result;
        CollectionUtils::collapse(callsEntries, result);
        return result;
    }

    virtual std::unordered_set<std::string> getProcsCalledBy(const std::string& callerProc) override
    {
        return CollectionUtils::find(callsEntries, callerProc)
            ? callsEntries[callerProc]
            : std::unordered_set<std::string>();
    }

    virtual std::unordered_set<std::string> getProcsCalling(const std::string& calleeProc) override
    {
        return CollectionUtils::find(reverseCallEntries, calleeProc)
            ? reverseCallEntries[calleeProc]
            : std::unordered_set<std::string>();
    }

    virtual bool isCalls(const std::string& callerProc, const std::string& calleeProc) override
    {
        return CollectionUtils::find(callsEntries, callerProc, calleeProc);
    }

    virtual bool hasCalls() override
    {
        return !callsEntries.empty();
    }

    virtual bool hasCallsByKey(const std::string &callerProc) override
    {
        return CollectionUtils::find(callsEntries, callerProc);
    }

    virtual bool hasCallsByValue(const std::string &calleeProc) override
    {
        return CollectionUtils::find(reverseCallEntries, calleeProc);
    }

    virtual std::unordered_map<std::string, std::unordered_set<std::string>> getCallsTEntries() override
    {
        return this->callsTEntries;
    }

    virtual std::unordered_set<std::string> getProcsCalledTBy(const std::string& callerProc) override
    {
        return CollectionUtils::find(callsTEntries, callerProc)
            ? callsTEntries[callerProc]
            : std::unordered_set<std::string>();
    }

    virtual std::unordered_set<std::string> getProcsCallingT(const std::string& calleeProc) override
    {
        return CollectionUtils::find(reverseCallTEntries, calleeProc)
            ? reverseCallTEntries[calleeProc]
            : std::unordered_set<std::string>();
    }

    virtual bool isCallsT(const std::string& callerProc, const std::string& calleeProc) override
    {
        return CollectionUtils::find(callsTEntries, callerProc, calleeProc);
    }

    virtual bool hasCallsT() override
    {
        return hasCalls();
    }

    virtual bool hasCallsTByKey(const std::string& callerProc) override
    {
        return hasCallsByKey(callerProc);
    }
    virtual bool hasCallsTByValue(const std::string& calleeProc) override
    {
        return hasCallsByValue(calleeProc);
    }
};
