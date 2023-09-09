// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "QueryGroup.h"
#include "common/CollectionUtils.h"

QueryGroup::QueryGroup() {}

void QueryGroup::addClause(std::shared_ptr<Clause> newClause) {
    std::unordered_set<std::string> newSynonyms = newClause->getSynonymList();

    for (auto& synonym : newSynonyms) {
        this->synonymList.emplace(synonym);
    }
    clauseGroup.push_back(newClause);
}

void QueryGroup::mergeGroup(QueryGroup& otherGroup) {
    for (int i = 0; i < otherGroup.clauseGroup.size(); i++) {
        addClause(otherGroup.clauseGroup[i]);
    }
}

bool QueryGroup::executeGroup(DI* diInterface) {
    bool querySuccess = true;
    std::unordered_set<std::string> processedSynonym;
    std::unordered_set<int> processedClause;
    int smallest = getSmallest(processedClause, processedSynonym);
    if (smallest == -1)
        return querySuccess;

    while (querySuccess) {
        int currentSmallest = getSmallest(processedClause, processedSynonym);
        if (currentSmallest == -1) {
            break;
        }
        std::shared_ptr<Clause> clause = clauseGroup[currentSmallest];
        processedClause.insert(currentSmallest);
        for (auto& syn : clause->getSynonymList()) {
            processedSynonym.insert(syn);
        }
        if (diInterface != nullptr) {
            clause->initializeClause(*diInterface);
        }

        ClauseResult currentResult = clause->process(groupResult);
        groupResult.mergeResult(currentResult);
        querySuccess = groupResult.isClauseSuccess();
    }

    return querySuccess;
}

int QueryGroup::getSmallest(std::unordered_set<int>& processedClause,
    std::unordered_set<std::string>& processedSynonym) {
    int smallest = -1;
    for (int i = 0; i < clauseGroup.size(); i++) {
        if (processedClause.count(i) > 0) {
            continue;
        }
        if (smallest == -1) {
            smallest = i;
            continue;
        }
        bool nextSmaller = Clause::ClauseComparator(processedSynonym)(clauseGroup[i],
            clauseGroup[smallest]);
        if (nextSmaller) {
            smallest = i;
        }
    }
    return smallest;
}

QueryResult QueryGroup::getResult(std::unordered_set<std::string> synonymToKeep) {
    groupResult.collapseResult(synonymToKeep);

    return this->groupResult;
}

std::unordered_set<std::string> QueryGroup::getSynonymList() {
    return this->synonymList;
}
