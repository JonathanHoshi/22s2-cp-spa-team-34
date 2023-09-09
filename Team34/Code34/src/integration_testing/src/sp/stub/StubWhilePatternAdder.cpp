#pragma once

#include "pkb/interfaces/IWhilePatternAdder.h"
#include "common/CollectionUtils.h"
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class StubWhilePatternAdder : public IWhilePatternAdder {
public:
    unordered_map<int, unordered_set<string>> patternMap;

    void addWhilePattern(const int& stmtNum, const unordered_set<string>& set) override {
        for (auto& var : set) {
            CollectionUtils::insert(patternMap, stmtNum, var);
        }
    }

    bool contains(int key, string val) {
        return CollectionUtils::find(patternMap, key, val);
    }

    int size(int key) {
        if (!CollectionUtils::find(patternMap, key)) {
            return 0;
        }
        return patternMap.at(key).size();
    }
};