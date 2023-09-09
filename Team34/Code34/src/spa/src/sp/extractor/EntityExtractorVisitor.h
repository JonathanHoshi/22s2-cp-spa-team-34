// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once
#include <string>
#include <unordered_map>
#include <unordered_set>
#include "ExtractorVisitor.h"
#include "pkb/interfaces/IProcAdder.h"
#include "pkb/interfaces/IConstAdder.h"
#include "pkb/interfaces/IVarAdder.h"
#include "pkb/interfaces/IStmtAdder.h"

// 'stmt' | 'read' | 'print' | 'call' | 'while'
//  'if' | 'assign' | 'variable' | 'constant' | 'procedure'


class EntityExtractorVisitor : public ExtractorVisitor {
public:
    EntityExtractorVisitor(IStmtAdder& stmtAdder,
        IProcAdder& procAdder, IConstAdder& constAdder, IVarAdder& varAdder);
    void extract(VariableNode& node) override;
    void extract(ConstantNode& node) override;
    void extract(ReadNode& node) override;
    void extract(PrintNode& node) override;
    void extract(ProcedureNode& node) override;
    void extract(CallNode& node) override;
    void extract(IfNode& node) override;
    void extract(WhileNode& node) override;
    void extract(AssignNode& node) override;
    void extract(OperatorNode& node) override;

    void transfer() override;

private:
    IStmtAdder* stmtAdder;
    IProcAdder* procAdder;
    IConstAdder* constAdder;
    IVarAdder* varAdder;

    std::unordered_set<std::string> variableLst;
    std::unordered_set<int> constantLst;
    std::unordered_set<std::string> procedureLst;
    std::unordered_map<int, std::string> readLst;
    std::unordered_map<int, std::string> printLst;
    std::unordered_map<int, std::string> callList;
    std::unordered_set<int> assignList;
    std::unordered_set<int> whileList;
    std::unordered_set<int> ifList;
};
