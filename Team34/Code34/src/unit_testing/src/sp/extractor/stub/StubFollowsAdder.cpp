#pragma once

#include <unordered_map>
#include <unordered_set>

#include "common/CollectionUtils.h"
#include "pkb/interfaces/IFollowsAdder.h"



class StubFollowsAdder : public IFollowsAdder {
public:
	std::unordered_map<int, int> followsMap;
    std::unordered_map<int, std::unordered_set<int>> followsTMap;

    bool containsFollow(const std::string& before, const std::string& after) {
        auto itor = followsMap.find(stoi(before));
        if (itor == followsMap.end())
            return false;
        int val = itor->second;
        return val == stoi(after);
    }

    void addRelation(const int& beforeStmt, const int& afterStmt) override {
        followsMap.insert({ beforeStmt, afterStmt });
    }

    void addRelationT(const int& beforeStmt, const int& afterStmt) override {
        CollectionUtils::insert(followsTMap, beforeStmt, afterStmt);
    }
};