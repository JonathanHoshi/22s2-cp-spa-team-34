// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "RootNode.h"
#include "sp/extractor/ExtractorVisitor.h"

RootNode::RootNode() {}

void RootNode::accept(ExtractorVisitor& e) {
    e.extract(*this);
}

// getters
ProcedureNode* RootNode::getProcedure(int i) {
    return this->procedures.at(i).get();
}

int RootNode::getProcedureCount() {
    return this->procedures.size();
}

// setters
void RootNode::addProcedure(std::shared_ptr<ProcedureNode> proc) {
    this->procedures.push_back(proc);
}

bool RootNode::operator==(const EntityNode& rhs) const {
    bool flag = true;

    if (typeid(*this) != typeid(rhs)) {
        return false;
    }
    const RootNode* root = dynamic_cast<const RootNode*>(&rhs);

    if (this->procedures.size() != root->procedures.size()) {
        return false;
    }

    for (int i = 0; i < procedures.size(); i++) {
        flag = flag && *(this->procedures.at(i)) == *(root->procedures.at(i));
    }

    return flag;
}

void RootNode::sortProcedure(std::vector<std::string>& sorted) {
    if (sorted.size() != procedures.size())
        throw std::out_of_range("toposort with improper size");
    std::unordered_map<std::string, std::shared_ptr<ProcedureNode>> map;
    for (auto prodNode : procedures) {
        map.insert({prodNode->getProcedureName(), prodNode});
    }
    procedures.clear();
    for (auto prodName : sorted) {
        auto itor = map.find(prodName);
        if (itor == map.end())
            throw std::out_of_range("procedure in toposort doesn't exist");
        procedures.push_back(itor->second);
    }
}
