#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
#include "common/CollectionUtils.h"
#include "pkb/interfaces/IParentAdder.h"



class StubParentAdder : public IParentAdder {

public:
    std::unordered_map<int, std::unordered_set<int>> parentMap;
    std::unordered_map<int, std::unordered_set<int>> parentTMap;

    bool containsParent(const int& parentStmt, const int& childStmt) {
        return CollectionUtils::find(parentMap, parentStmt, childStmt);
    }

    void addRelation(const int& parentStmt, const int& childStmt) override {
        CollectionUtils::insert(parentMap, parentStmt, childStmt);
    }

    void addRelationT(const int& parentStmt, const int& childStmt) override {
        CollectionUtils::insert(parentTMap, parentStmt, childStmt);
    }
};