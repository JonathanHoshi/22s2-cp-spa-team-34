// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once
#include "common/exceptions/TransverseError.h"

class VariableNode;
class ConstantNode;
class OperatorNode;
class ReadNode;
class PrintNode;
class CallNode;
class IfNode;
class WhileNode;
class AssignNode;
class ProcedureNode;
class StmtLstNode;
class RootNode;

class ExtractorVisitor {
public:
    virtual void extract(VariableNode& node) = 0;
    virtual void extract(ConstantNode& node) = 0;
    virtual void extract(OperatorNode& node) = 0;

    virtual void extract(ReadNode& node) = 0;
    virtual void extract(PrintNode& node) = 0;
    virtual void extract(CallNode& node) = 0;
    virtual void extract(IfNode& node) = 0;
    virtual void extract(WhileNode& node) = 0;
    virtual void extract(AssignNode& node) = 0;

    virtual void extract(ProcedureNode& node);
    virtual void extract(StmtLstNode& node);
    virtual void extract(RootNode& node);

    virtual void begin(RootNode& node);
    virtual void transfer() = 0;
};
