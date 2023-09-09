// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once
#include <vector>
#include <memory>
#include "EntityNode.h"
#include "StmtNode.h"

class StmtLstNode : public EntityNode {
private:
    std::vector<std::shared_ptr<StmtNode>> stmts;

public:
    StmtLstNode();
    void accept(ExtractorVisitor& e) override;

    // getter
    StmtNode* getStmt(int i);
    int getStmtCount();

    // setters
    void addStmt(std::shared_ptr<StmtNode> stmt);

    bool operator==(const EntityNode& rhs) const;
};
