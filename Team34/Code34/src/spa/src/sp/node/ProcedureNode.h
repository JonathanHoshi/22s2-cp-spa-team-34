// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once
#include <string>
#include <memory>
#include "EntityNode.h"
#include "StmtLstNode.h"

class ProcedureNode : public EntityNode {
protected:
    std::shared_ptr<StmtLstNode> stmtList;
    std::string procedureName;

public:
    explicit ProcedureNode(std::string name);
    void accept(ExtractorVisitor& e) override;

    // getter
    StmtLstNode* getStmtList();
    std::string getProcedureName();

    // setter
    void setStmtList(std::shared_ptr<StmtLstNode> stmtList);

    bool operator==(const EntityNode& rhs) const;
};
