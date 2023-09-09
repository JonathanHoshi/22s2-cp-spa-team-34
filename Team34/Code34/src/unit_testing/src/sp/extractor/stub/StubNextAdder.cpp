#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
#include "common/CollectionUtils.h"
#include "pkb/interfaces/INextAdder.h"



class StubNextAdder : public INextAdder {
public:
    std::unordered_map<int, std::unordered_set<int>> nextMap;

    bool containsNext(const int& parentStmt, const int& childStmt) {
        return CollectionUtils::find(nextMap, parentStmt, childStmt);
    }

    void addNext(const int& parentStmt, const int& childStmt) override {
        CollectionUtils::insert(nextMap, parentStmt, childStmt);
    }
};