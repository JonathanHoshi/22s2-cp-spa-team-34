// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "QueryProcessor.h"

int QueryProcessor::handleGroupUnion(int group1, int group2) {
    std::unordered_set<std::string> group1Synonyms = groupMap[group1].getSynonymList();
    std::unordered_set<std::string> group2Synonyms = groupMap[group2].getSynonymList();

    int biggerGroup = (group1Synonyms.size() > group2Synonyms.size())
        ? group1
        : group2;
    int smallerGroup = (group1Synonyms.size() <= group2Synonyms.size())
        ? group1
        : group2;

    groupMap[biggerGroup].mergeGroup(groupMap[smallerGroup]);

    for (auto& synonym : groupMap[smallerGroup].getSynonymList()) {
        synonymToGroupMap[synonym] = biggerGroup;
    }

    groupMap.erase(smallerGroup);
    return biggerGroup;
}

void QueryProcessor::handleClauseGrouping(std::shared_ptr<Clause>& clause) {
    std::unordered_set<std::string> synonymList = clause->getSynonymList();

    if (synonymList.empty()) {
        addClauseToGroup(0, clause);
        return;
    }

    // only can 0/1/2 groups as max 2 synonyms
    std::unordered_set<int> groupSet;

    for (auto& synonym : synonymList) {
        auto iter = synonymToGroupMap.find(synonym);
        if (iter != synonymToGroupMap.end()) {
            groupSet.emplace(iter->second);
        }
    }

    std::vector<int> groupList(groupSet.begin(), groupSet.end());

    int groupNo;

    if (groupList.empty()) {
        groupNo = newGroupIndex;
    } else if (groupList.size() == 1) {
        groupNo = groupList[0];
    } else {
        groupNo = handleGroupUnion(groupList[0], groupList[1]);
    }

    addClauseToGroup(groupNo, clause);
    addSynonymListToGroup(groupNo, synonymList);
}

void QueryProcessor::addClauseToGroup(int index, std::shared_ptr<Clause>& clause) {
    if (groupMap.find(index) == groupMap.end()) {
        groupMap.emplace(index, QueryGroup());
        newGroupIndex++;
    }
    groupMap[index].addClause(clause);
}

void QueryProcessor::addSynonymListToGroup(int index,
    std::unordered_set<std::string>& synonymList) {
    for (auto& synonym : synonymList) {
        synonymToGroupMap.emplace(synonym, index);
    }
}

void QueryProcessor::groupClause(std::vector<std::shared_ptr<Clause>>& clauseList) {
    for (auto& clause : clauseList) {
        handleClauseGrouping(clause);
    }
}

bool QueryProcessor::processGroup(DI* di) {
    for (auto& [groupNo, group] : groupMap) {
        bool groupStatus = group.executeGroup(di);

        if (!groupStatus) {
            return false;
        }
    }
    return true;
}

QueryProcessor::QueryProcessor() {
    groupMap.emplace(0, QueryGroup());  // no synonym group
    newGroupIndex = 1;  // starting group index
}

bool QueryProcessor::processQuery(std::vector<std::shared_ptr<Clause>>& clauseList, DI* di) {
    groupClause(clauseList);
    return processGroup(di);
}

QueryResult QueryProcessor::
processResult(std::vector<std::shared_ptr<EntityArgument>>& selectList, DI* di) {
    QueryResult finalResult;

    std::unordered_set<int> groupSet;
    std::unordered_set<std::string> synonymList;
    std::unordered_set<std::shared_ptr<EntityArgument>> noGroupSynonym;

    for (std::shared_ptr<EntityArgument>& arg : selectList) {
        if (di != nullptr) {
            arg->setPKBInterface(*di);
        }

        auto iter = synonymToGroupMap.find(arg->getValue());

        if (iter != synonymToGroupMap.end()) {
            groupSet.emplace(iter->second);
        } else {
            noGroupSynonym.emplace(arg);
        }
        synonymList.emplace(arg->getValue());
    }

    for (int groupNo : groupSet) {
        QueryResult groupResult = groupMap[groupNo].getResult(synonymList);
        finalResult.mergeResult(groupResult);
    }

    for (auto& entity : noGroupSynonym) {
        std::unordered_set<std::string> pkbSet = entity->getPKBValueList();
        finalResult.addSynonymGroup(entity->getValue(), pkbSet);
    }

    return finalResult;
}
