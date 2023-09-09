// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once
#include "EntityNode.h"

class StmtNode : public EntityNode {
protected:
    int stmtNo;
    explicit StmtNode(int stmtNo);

public:
    int getStmtNumber();
    virtual bool operator==(const StmtNode& rhs) const = 0;
};
