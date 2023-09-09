#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "common/CollectionUtils.h"
#include "pkb/interfaces/IModifiesGetter.h"



class StubModifiesGetter : public IModifiesGetter
{
private:
    std::unordered_map<int, std::unordered_set<std::string>> modifiesSEntries;
    std::unordered_map<std::string, std::unordered_set<std::string>> modifiesPEntries;

public:
    void setModifiesSEntries(std::unordered_map<int, std::unordered_set<std::string>>& modifiesSEntries) {
        this->modifiesSEntries = modifiesSEntries;
    }

    void setModifiesPEntries(std::unordered_map<std::string, std::unordered_set<std::string>>& modifiesPEntries) {
        this->modifiesPEntries = modifiesPEntries;
    }

    // ---------- Modifies: Statements ----------
    // Gets all stmt-modifies-var entries
    virtual std::unordered_map<int, std::unordered_set<std::string>> getStmtVarEntries() override 
    {
        return this->modifiesSEntries;
    }

    // Gets var modified by stmtNum
    virtual std::unordered_set<std::string> getVarsByStmt(const int& stmtNum) override
    {
        return CollectionUtils::find(modifiesSEntries, stmtNum)
            ? modifiesSEntries[stmtNum] : std::unordered_set<std::string>();
    }

    // Gets set of stmts that modify varName
    virtual std::unordered_set<int> getStmtsByVar(const std::string& varName) override
    { 
        std::unordered_set<int> result;
        CollectionUtils::getKeySetByValue(modifiesSEntries, varName, result);
        return result;
    }

    // Gets set of vars that are modified by some stmt
    virtual std::unordered_set<std::string> getVarsInStmts() override
    {
        std::unordered_set<std::string> result;
        CollectionUtils::collapse(modifiesSEntries, result);
        return result;
    }

    // Gets set of stmts that modifies some var
    virtual std::unordered_set<int> getStmts() override
    {
        std::unordered_set<int> result;
        CollectionUtils::collapseKey(modifiesSEntries, result);
        return result;
    }

    // Checks if stmtNum modifies varName
    virtual bool isAssociatedS(const int& stmtNum, const std::string& varName) override
    {
        return CollectionUtils::find(modifiesSEntries, stmtNum, varName);
    }

    // Checks if there contains at least one modifies S
    virtual bool hasAssociatedS() override
    {
        return !modifiesSEntries.empty();
    }

    // Checks if stmtNum is modifies S
    virtual bool hasAssociatedSByKey(const int& stmtNum) override
    {
        return !getVarsByStmt(stmtNum).empty();
    }

    // Checks if varName is modifies S
    virtual bool hasAssociatedSByValue(const std::string& varName) override
    {
        return !getStmtsByVar(varName).empty();
    }

    // ---------- Modifies: Procedures ----------
    // Gets all proc-modifies-var entries
    virtual std::unordered_map<std::string, std::unordered_set<std::string>> getProcVarEntries() override 
    {
        return this->modifiesPEntries;
    }

    // Gets set of vars modified by procName
    virtual std::unordered_set<std::string> getVarsByProc(const std::string& procName) override
    {
        return CollectionUtils::find(modifiesPEntries, procName)
            ? modifiesPEntries[procName] : std::unordered_set<std::string>();
    }

    // Gets set of procs that modify varName
    virtual std::unordered_set<std::string> getProcsByVar(const std::string& varName) override
    {
        std::unordered_set<std::string> result;
        CollectionUtils::getKeySetByValue(modifiesPEntries, varName, result);
        return result;
    }

    // Gets set of vars that are modified by some proc
    virtual std::unordered_set<std::string> getVarsInProcs() override
    {
        std::unordered_set<std::string> result;
        CollectionUtils::collapse(modifiesPEntries, result);
        return result;
    }

    // Gets set of procs that modifies some var
    virtual std::unordered_set<std::string> getProcs() override
    {
        std::unordered_set<std::string> result;
        CollectionUtils::collapseKey(modifiesPEntries, result);
        return result;
    }

    // Checks if procName modifies varName
    virtual bool isAssociatedP(const std::string& procName, const std::string& varName) override
    {
        return CollectionUtils::find(modifiesPEntries, procName, varName);
    }

    // Checks if there contains at least one modifies P
    virtual bool hasAssociatedP() override
    {
        return !modifiesPEntries.empty();
    }

    // Checks if procName is modifies P
    virtual bool hasAssociatedPByKey(const std::string& procName) override
    {
        return !getVarsByProc(procName).empty();
    }

    // Checks if varName is modifies P
    virtual bool hasAssociatedPByValue(const std::string& varName) override
    {
        return !getProcsByVar(varName).empty();
    }
};
