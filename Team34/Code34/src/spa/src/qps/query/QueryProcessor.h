// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once

#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <vector>

#include "di/DI.h"
#include "qps/argument/Argument.h"
#include "qps/argument/entity/EntityArgument.h"
#include "qps/clause/Clause.h"
#include "qps/query/QueryGroup.h"

class QueryProcessor {
private:
    std::unordered_map<std::string, int> synonymToGroupMap;
    std::unordered_map<int, QueryGroup> groupMap;
    int newGroupIndex;

    int handleGroupUnion(int group1, int group2);
    void handleClauseGrouping(std::shared_ptr<Clause>& clause);
    void addClauseToGroup(int index, std::shared_ptr<Clause>& clause);
    void addSynonymListToGroup(int index, std::unordered_set<std::string>& synonymList);
    void groupClause(std::vector<std::shared_ptr<Clause>>& clauseList);
    bool processGroup(DI* di);

public:
    QueryProcessor();
    bool processQuery(std::vector<std::shared_ptr<Clause>>& clauseList, DI* di);
    QueryResult processResult(std::vector<std::shared_ptr<EntityArgument>>& selectList, DI* di);
};
