// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once

#include <unordered_map>
#include <unordered_set>
#include <string>
#include <memory>
#include <queue>
#include <vector>
#include "qps/clause/Clause.h"
#include "qps/query/QueryResult.h"



class QueryGroup {
private:
    std::vector<std::shared_ptr<Clause>> clauseGroup;
    QueryResult groupResult;
    std::unordered_set<std::string> synonymList;

    int getSmallest(std::unordered_set<int>& processedClause,
        std::unordered_set<std::string>& processedSynonym);
public:
    QueryGroup();
    void addClause(std::shared_ptr<Clause> newClause);
    void mergeGroup(QueryGroup& otherGroup);
    bool executeGroup(DI* diInterface);
    QueryResult getResult(std::unordered_set<std::string> synonymToKeep);
    std::unordered_set<std::string> getSynonymList();
};
