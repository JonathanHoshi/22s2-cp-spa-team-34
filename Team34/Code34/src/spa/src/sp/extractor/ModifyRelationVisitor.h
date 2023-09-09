// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once
#include "VariableRelationVisitor.h"
#include "pkb/interfaces/IModifiesAdder.h"

class ModifyRelationVisitor : public VariableRelationVisitor {
public:
    explicit ModifyRelationVisitor(IModifiesAdder& adder);
    void extract(VariableNode& node) override;
    void extract(ConstantNode& node) override;
    void extract(ReadNode& node) override;
    void extract(PrintNode& node) override;
    void extract(ProcedureNode& node) override;

    void extract(IfNode& node) override;
    void extract(WhileNode& node) override;
    void extract(AssignNode& node) override;

    void extract(OperatorNode& node) override;

    void transfer() override;

protected:
    IModifiesAdder* adder;
};
