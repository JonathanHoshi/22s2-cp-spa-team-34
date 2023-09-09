// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once
#include <string>
#include "StmtNode.h"

class CallNode : public StmtNode {
protected:
    std::string procedureCall;

public:
    CallNode(int stmtNo, std::string procedureCall);
    void accept(ExtractorVisitor& e) override;

    // getter
    std::string getProcedureName();

    bool operator==(const StmtNode& rhs) const override;
};
