// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once
#include <unordered_map>
#include <unordered_set>
#include <string>

#include "ExtractorVisitor.h"

class VariableRelationVisitor : public ExtractorVisitor {
protected:
    VariableRelationVisitor();
    std::unordered_map<std::string, std::unordered_set<std::string>> procedureMap;
    std::unordered_map<int, std::unordered_set<std::string>> statementMap;
    void mergeStmtList(std::unordered_set<std::string>& copyTo, StmtLstNode& stmtList);

    void extract(CallNode& node) override;
};
