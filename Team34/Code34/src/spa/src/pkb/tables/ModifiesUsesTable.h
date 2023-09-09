// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once

#include <unordered_map>
#include <unordered_set>
#include <string>
#include "pkb/base/BaseMapSet.h"
#include "pkb/interfaces/IModifiesAdder.h"
#include "pkb/interfaces/IModifiesGetter.h"
#include "pkb/interfaces/IUsesAdder.h"
#include "pkb/interfaces/IUsesGetter.h"

class ModifiesUsesTable : public IModifiesGetter, public IModifiesAdder,
                          public IUsesGetter, public IUsesAdder {
private:
    // <stmt_num, var_associated>
    BaseMapSet<int, std::string> stmtToVarEntries;
    // <var_name, set_of_stmt_nums_associated_to_var>
    BaseMapSet<std::string, int> varToStmtEntries;
    // <proc_name, set_of_vars_associated>
    BaseMapSet<std::string, std::string> procToVarEntries;
    // <var_name, set_of_procs_associated_to_var>
    BaseMapSet<std::string, std::string> varToProcEntries;

public:
    // ---------- Statements ----------
    std::unordered_map<int, std::unordered_set<std::string>> getStmtVarEntries() override;
    std::unordered_set<std::string> getVarsByStmt(const int& stmtNum) override;
    std::unordered_set<int> getStmtsByVar(const std::string& varName) override;
    std::unordered_set<std::string> getVarsInStmts() override;
    std::unordered_set<int> getStmts() override;
    bool isAssociatedS(const int& stmtNum, const std::string& varName) override;
    bool hasAssociatedS() override;
    bool hasAssociatedSByKey(const int& stmtNum) override;
    bool hasAssociatedSByValue(const std::string& varName) override;
    void addVarS(const int& stmtNum, const std::string& varName) override;

    // ---------- Procedures ----------
    std::unordered_map<std::string, std::unordered_set<std::string>> getProcVarEntries() override;
    std::unordered_set<std::string> getVarsByProc(const std::string& procName) override;
    std::unordered_set<std::string> getProcsByVar(const std::string& varName) override;
    std::unordered_set<std::string> getVarsInProcs() override;
    std::unordered_set<std::string> getProcs() override;
    bool isAssociatedP(const std::string& procName, const std::string& varName) override;
    bool hasAssociatedP() override;
    bool hasAssociatedPByKey(const std::string& procName) override;
    bool hasAssociatedPByValue(const std::string& varName) override;
    void addVarP(const std::string& procName, const std::string& varName) override;
};
