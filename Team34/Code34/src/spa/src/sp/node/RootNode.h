// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once
#include <stdexcept>
#include <stack>
#include <unordered_map>
#include <string>
#include <memory>
#include <vector>
#include "EntityNode.h"
#include "ProcedureNode.h"

class RootNode : public EntityNode {
protected:
    std::vector<std::shared_ptr<ProcedureNode>> procedures;

public:
    RootNode();
    void accept(ExtractorVisitor& e) override;

    // getters
    ProcedureNode* getProcedure(int i);
    int getProcedureCount();

    // setters
    void addProcedure(std::shared_ptr<ProcedureNode> proc);

    void sortProcedure(std::vector<std::string>& sorted);

    bool operator==(const EntityNode& rhs) const;
};
