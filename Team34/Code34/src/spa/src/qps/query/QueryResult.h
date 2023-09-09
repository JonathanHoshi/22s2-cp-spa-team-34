// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once

#include <unordered_map>
#include <unordered_set>
#include <string>
#include <memory>
#include <vector>
#include "qps/clause/ClauseResult.h"

class QueryResult {
private:
    std::unordered_map<std::string, std::vector<std::string>> resultTable;
    std::vector<std::string> synonymList;
    bool isQuerySuccess;

    void addEntry(std::string synonym, std::string value);
    void addEntry(std::vector<std::string>& entryValues);
    void addEntry(std::vector<std::string>& entryValues1, std::vector<std::string>& entryValues2);
    void removeEntry(int entryIndex);
    std::vector<std::string> getEntryValue(int entryIndex);

    std::string collapseString(std::vector<std::string>& entryDataList, std::string delimiter);

    void addSingleSynonym(std::string syn, std::unordered_set<std::string>& synValues);
    void addDoubleSynonym(std::string syn1, std::string syn2, std::unordered_map<std::string,
        std::unordered_set<std::string>>& synValues);

    void handleAddEntryWithSet(std::vector<std::string>& entryDataList,
        std::unordered_set<std::string>& synValues);
    void handleAddEntryWithMap(std::vector<std::string>& entryDataList,
        std::unordered_map<std::string, std::unordered_set<std::string>>& synValues);
    void handleAddEntryWithFilter(std::vector<std::string>& entryDataList,
        std::unordered_set<std::string>& existingValues);
    void handleSingleMerge(std::string syn, std::unordered_set<std::string>& resultSet);
    void handleDoubleMerge(std::string syn1, std::string syn2,
        std::unordered_map<std::string, std::unordered_set<std::string>>& resultMapSet);

    void filterSingleSynonym(std::string syn, std::unordered_set<std::string>& synValues);
    void filterDoubleSynonym(std::string syn1, std::string syn2, std::unordered_map<std::string,
        std::unordered_set<std::string>>& synValues);

    void crossProductSingle(std::string syn, std::unordered_set<std::string>& synValues);
    void crossProductSingleWithPairRef(std::string synonym, std::string synonymRef,
        std::unordered_map<std::string, std::unordered_set<std::string>>& synValues,
        bool isKeyRef);
    void crossProductDouble(std::string syn1, std::string syn2,
        std::unordered_map<std::string, std::unordered_set<std::string>>& synValues);

public:
    QueryResult();
    explicit QueryResult(bool queryStatus);

    bool hasSynonym(std::string synonym);
    bool isClauseSuccess();
    std::unordered_set<std::string> getSynonymValues(std::string synonym);
    std::unordered_map<std::string,
        std::unordered_set<std::string>> getSynonymPair(std::string syn1, std::string syn2);

    void addSynonymGroup(std::string synonym, std::unordered_set<std::string>& valueSet);
    void mergeResult(ClauseResult& clauseResult);
    void mergeResult(QueryResult& otherResult);
    void collapseResult(std::unordered_set<std::string>& synonymToKeep);

    std::unordered_map<std::string, std::vector<std::string>>& getResultMap();
};
