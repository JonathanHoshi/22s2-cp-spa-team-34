#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "common/CollectionUtils.h"
#include "pkb/interfaces/IUsesGetter.h"



class StubUsesGetter : public IUsesGetter
{
private:
    std::unordered_map<int, std::unordered_set<std::string>> usesSEntries;
    std::unordered_map<std::string, std::unordered_set<std::string>> usesPEntries;

public:
    void setUsesSEntries(std::unordered_map<int, std::unordered_set<std::string>>& usesSEntries) {
        this->usesSEntries = usesSEntries;
    }

    void setUsesPEntries(std::unordered_map<std::string, std::unordered_set<std::string>>& usesPEntries) {
        this->usesPEntries = usesPEntries;
    }

    // ---------- Uses: Statements ----------
    // Gets all stmt-uses-var entries
    virtual std::unordered_map<int, std::unordered_set<std::string>> getStmtVarEntries() override 
    {
        return this->usesSEntries;
    }

    // Gets var used by stmtNum
    virtual std::unordered_set<std::string> getVarsByStmt(const int& stmtNum) override
    {
        return CollectionUtils::find(usesSEntries, stmtNum) 
            ? usesSEntries[stmtNum] : std::unordered_set<std::string>();
    }

    // Gets set of stmts that modify varName
    virtual std::unordered_set<int> getStmtsByVar(const std::string& varName) override
    { 
        std::unordered_set<int> result;
        CollectionUtils::getKeySetByValue(usesSEntries, varName, result);
        return result;
    }

    // Gets set of vars that are used by some stmt
    virtual std::unordered_set<std::string> getVarsInStmts() override
    {
        std::unordered_set<std::string> result;
        CollectionUtils::collapse(usesSEntries, result);
        return result;
    }

    // Gets set of stmts that uses some var
    virtual std::unordered_set<int> getStmts() override
    {
        std::unordered_set<int> result;
        CollectionUtils::collapseKey(usesSEntries, result);
        return result;
    }

    // Checks if stmtNum uses varName
    virtual bool isAssociatedS(const int& stmtNum, const std::string& varName) override
    {
        return CollectionUtils::find(usesSEntries, stmtNum, varName);
    }

    // Checks if there contains at least one uses S
    virtual bool hasAssociatedS() override
    {
        return !usesSEntries.empty();
    }

    // Checks if stmtNum is uses S
    virtual bool hasAssociatedSByKey(const int& stmtNum) override
    {
        return !getVarsByStmt(stmtNum).empty();
    }

    // Checks if varName is uses S
    virtual bool hasAssociatedSByValue(const std::string& varName) override
    {
        return !getStmtsByVar(varName).empty();
    }

    // ---------- Uses: Procedures ----------
    // Gets all proc-uses-var entries
    virtual std::unordered_map<std::string, std::unordered_set<std::string>> getProcVarEntries() override 
    {
        return this->usesPEntries;
    }

    // Gets set of vars used by procName
    virtual std::unordered_set<std::string> getVarsByProc(const std::string& procName) override
    {
        return CollectionUtils::find(usesPEntries, procName)
            ? usesPEntries[procName] : std::unordered_set<std::string>();
    }

    // Gets set of procs that modify varName
    virtual std::unordered_set<std::string> getProcsByVar(const std::string& varName) override
    {
        std::unordered_set<std::string> result;
        CollectionUtils::getKeySetByValue(usesPEntries, varName, result);
        return result;
    }

    // Gets set of vars that are used by some proc
    virtual std::unordered_set<std::string> getVarsInProcs() override
    {
        std::unordered_set<std::string> result;
        CollectionUtils::collapse(usesPEntries, result);
        return result;
    }

    // Gets set of procs that uses some var
    virtual std::unordered_set<std::string> getProcs() override
    {
        std::unordered_set<std::string> result;
        CollectionUtils::collapseKey(usesPEntries, result);
        return result;
    }

    // Checks if procName uses varName
    virtual bool isAssociatedP(const std::string& procName, const std::string& varName) override
    {
        return CollectionUtils::find(usesPEntries, procName, varName);
    }

    // Checks if there contains at least one uses P
    virtual bool hasAssociatedP() override
    {
        return !usesPEntries.empty();
    }

    // Checks if procName is uses P
    virtual bool hasAssociatedPByKey(const std::string& procName) override
    {
        return !getVarsByProc(procName).empty();
    }

    // Checks if varName is uses P
    virtual bool hasAssociatedPByValue(const std::string& varName) override
    {
        return !getProcsByVar(varName).empty();
    }
};
