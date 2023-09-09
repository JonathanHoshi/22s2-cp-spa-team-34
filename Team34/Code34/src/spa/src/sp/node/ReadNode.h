// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once
#include <memory>
#include "StmtNode.h"
#include "VariableNode.h"

class ReadNode : public StmtNode {
protected:
    std::shared_ptr<VariableNode> readVar;

public:
    explicit ReadNode(int stmtNo);
    void accept(ExtractorVisitor& e) override;

    // getter
    VariableNode* getVariable();

    // setter
    void setVariable(std::shared_ptr<VariableNode> node);

    bool operator==(const StmtNode& rhs) const override;
};
