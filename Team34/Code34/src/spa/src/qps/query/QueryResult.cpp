// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "QueryResult.h"
#include "common/CollectionUtils.h"

void QueryResult::addEntry(std::string synonym, std::string value) {
    if (resultTable.find(synonym) == resultTable.end()) {
        resultTable.emplace(synonym, std::vector<std::string>());
    }

    resultTable.at(synonym).push_back(value);
}

void QueryResult::addEntry(std::vector<std::string>& entryValues) {
    for (int i = 0; i < entryValues.size(); i++) {
        addEntry(synonymList[i], entryValues[i]);
    }
}

void QueryResult::addEntry(std::vector<std::string>& entryValues1,
    std::vector<std::string>& entryValues2) {
    for (int i = 0; i < entryValues1.size(); i++) {
        addEntry(synonymList[i], entryValues1[i]);
    }

    for (int i = 0; i < entryValues2.size(); i++) {
        addEntry(synonymList[entryValues1.size() + i], entryValues2[i]);
    }
}

void QueryResult::removeEntry(int entryIndex) {
    for (auto& [synonym, valueSet] : resultTable) {
        valueSet.erase(valueSet.begin() + entryIndex);
    }
}

std::vector<std::string> QueryResult::getEntryValue(int entryIndex) {
    std::vector<std::string> entryValues;

    for (int i = 0; i < synonymList.size(); i++) {
        entryValues.push_back(resultTable.at(synonymList[i])[entryIndex]);
    }

    return entryValues;
}

std::string QueryResult::collapseString(std::vector<std::string>& entryList,
    std::string delimiter) {
    std::string result;
    for (int i = 0; i < entryList.size(); i++) {
        result += entryList[i];

        if (i >= entryList.size() - 1) {
            break;
        }

        result += delimiter;
    }
    return result;
}

void QueryResult::addSingleSynonym(std::string syn, std::unordered_set<std::string>& synValues) {
    synonymList.push_back(syn);
    resultTable.emplace(syn, std::vector<std::string>(synValues.begin(), synValues.end()));
}

void QueryResult::addDoubleSynonym(std::string syn1, std::string syn2,
    std::unordered_map<std::string, std::unordered_set<std::string>>& synValues) {
    std::vector<std::string> syn1List;
    std::vector<std::string> syn2List;

    for (auto& [syn1Value, syn2ValueSet] : synValues) {
        for (std::string syn2Value : syn2ValueSet) {
            syn1List.push_back(syn1Value);
            syn2List.push_back(syn2Value);
        }
    }

    synonymList.push_back(syn1);
    synonymList.push_back(syn2);
    resultTable.emplace(syn1, syn1List);
    resultTable.emplace(syn2, syn2List);
}

void QueryResult::handleAddEntryWithSet(std::vector<std::string>& entryDataList,
    std::unordered_set<std::string>& synValues) {
    for (std::string entry : synValues) {
        for (int i = 0; i < entryDataList.size(); i++) {
            addEntry(synonymList[i], entryDataList[i]);
        }
        addEntry(synonymList[synonymList.size() - 1], entry);
    }
}

void QueryResult::handleAddEntryWithMap(std::vector<std::string>& entryDataList,
    std::unordered_map<std::string, std::unordered_set<std::string>>& synValues) {
    for (auto& [key, valueSet] : synValues) {
        std::vector<std::string> updatedEntryData = entryDataList;
        updatedEntryData.push_back(key);
        handleAddEntryWithSet(updatedEntryData, valueSet);
    }
}

void QueryResult::handleAddEntryWithFilter(std::vector<std::string>& entryDataList,
    std::unordered_set<std::string>& existingValues) {
    std::string delimeter = "-";
    std::string entryString = collapseString(entryDataList, delimeter);

    if (existingValues.find(entryString) == existingValues.end()) {
        existingValues.emplace(entryString);
        addEntry(entryDataList);
    }
}

void QueryResult::handleSingleMerge(std::string syn, std::unordered_set<std::string>& resultSet) {
    if (hasSynonym(syn)) {
        filterSingleSynonym(syn, resultSet);
    } else {
        crossProductSingle(syn, resultSet);
    }
}

void QueryResult::handleDoubleMerge(std::string syn1, std::string syn2,
    std::unordered_map<std::string, std::unordered_set<std::string>>& resultMapSet) {
    bool isFirstSynonymNew = !hasSynonym(syn1);
    bool isSecondSynonymNew = !hasSynonym(syn2);

    if (isFirstSynonymNew && !isSecondSynonymNew) {
        std::unordered_set<std::string> valueSet;
        CollectionUtils::collapse(resultMapSet, valueSet);
        filterSingleSynonym(syn2, valueSet);
        crossProductSingleWithPairRef(syn1, syn2, resultMapSet, false);
    } else if (!isFirstSynonymNew && isSecondSynonymNew) {
        std::unordered_set<std::string> keySet;
        CollectionUtils::collapseKey(resultMapSet, keySet);
        filterSingleSynonym(syn1, keySet);
        crossProductSingleWithPairRef(syn2, syn1, resultMapSet, true);
    } else if (isFirstSynonymNew && isSecondSynonymNew) {
        crossProductDouble(syn1, syn2, resultMapSet);
    } else {
        filterDoubleSynonym(syn1, syn2, resultMapSet);
    }
}

void QueryResult::filterSingleSynonym(std::string syn,
    std::unordered_set<std::string>& synValues) {
    QueryResult filterResult;

    filterResult.synonymList = this->synonymList;
    int curResultSize = resultTable.begin()->second.size();

    for (int i = 0; i < curResultSize; i++) {
        if (CollectionUtils::find(synValues, resultTable[syn][i])) {
            std::vector<std::string> entryValues = getEntryValue(i);
            filterResult.addEntry(entryValues);
        }
    }

    this->resultTable = filterResult.resultTable;
    this->synonymList = filterResult.synonymList;
}

void QueryResult::filterDoubleSynonym(std::string syn1, std::string syn2,
    std::unordered_map<std::string, std::unordered_set<std::string>>& synValues) {
    QueryResult filterResult;

    filterResult.synonymList = this->synonymList;
    int curResultSize = resultTable.begin()->second.size();

    for (int i = 0; i < curResultSize; i++) {
        if (CollectionUtils::find(synValues, resultTable[syn1][i], resultTable[syn2][i])) {
            std::vector<std::string> entryValues = getEntryValue(i);
            filterResult.addEntry(entryValues);
        }
    }

    this->resultTable = filterResult.resultTable;
    this->synonymList = filterResult.synonymList;
}

void QueryResult::crossProductSingle(std::string syn, std::unordered_set<std::string>& synValues) {
    if (resultTable.empty()) {
        addSingleSynonym(syn, synValues);
        return;
    }

    QueryResult newResult;
    newResult.synonymList = this->synonymList;
    newResult.synonymList.push_back(syn);

    int resultTableSize = resultTable.begin()->second.size();

    for (int i = 0; i < resultTableSize; i++) {
        std::vector<std::string> entryValues = getEntryValue(i);
        newResult.handleAddEntryWithSet(entryValues, synValues);
    }

    resultTable = newResult.resultTable;
    synonymList = newResult.synonymList;
}

void QueryResult::crossProductSingleWithPairRef(std::string synonym, std::string synonymRef,
    std::unordered_map<std::string, std::unordered_set<std::string>>& synValues, bool isKeyRef) {
    QueryResult newResult;
    newResult.synonymList = this->synonymList;
    newResult.synonymList.push_back(synonym);

    int resultTableSize = resultTable.begin()->second.size();

    for (int i = 0; i < resultTableSize; i++) {
        std::vector<std::string> entryValues = getEntryValue(i);
        std::unordered_set<std::string> newEntryData;
        if (isKeyRef) {
            newEntryData = synValues.at((resultTable.at(synonymRef)[i]));
        } else {
            CollectionUtils::getKeySetByValue(synValues,
                resultTable.at(synonymRef)[i], newEntryData);
        }
        newResult.handleAddEntryWithSet(entryValues, newEntryData);
    }

    resultTable = newResult.resultTable;
    synonymList = newResult.synonymList;
}

void QueryResult::crossProductDouble(std::string syn1, std::string syn2,
    std::unordered_map<std::string, std::unordered_set<std::string>>& synValues) {
    if (resultTable.empty()) {
        addDoubleSynonym(syn1, syn2, synValues);
        return;
    }

    QueryResult newResult;
    newResult.synonymList = this->synonymList;
    newResult.synonymList.push_back(syn1);
    newResult.synonymList.push_back(syn2);

    int resultTableSize = resultTable.begin()->second.size();

    for (int i = 0; i < resultTableSize; i++) {
        std::vector<std::string> entryValues = getEntryValue(i);
        newResult.handleAddEntryWithMap(entryValues, synValues);
    }

    resultTable = newResult.resultTable;
    synonymList = newResult.synonymList;
}

QueryResult::QueryResult() : QueryResult(true) { }

QueryResult::QueryResult(bool queryStatus) {
    this->isQuerySuccess = queryStatus;
}

bool QueryResult::hasSynonym(std::string synonym) {
    return this->resultTable.find(synonym) != this->resultTable.end();
}

bool QueryResult::isClauseSuccess() {
    return this->isQuerySuccess;
}

std::unordered_set<std::string> QueryResult::getSynonymValues(std::string synonym) {
    if (resultTable.empty()) {
        return std::unordered_set<std::string>();
    }

    std::vector<std::string> valueList = resultTable.at(synonym);
    std::unordered_set<std::string> valueSet(valueList.begin(), valueList.end());

    return valueSet;
}

std::unordered_map<std::string, std::unordered_set<std::string>> QueryResult::
getSynonymPair(std::string syn1, std::string syn2) {
    if (resultTable.empty()) {
        return std::unordered_map<std::string, std::unordered_set<std::string>>();
    }

    std::unordered_map<std::string, std::unordered_set<std::string>> synonymPair;

    int resultTableSize = resultTable.begin()->second.size();

    for (int i = 0; i < resultTableSize; i++) {
        CollectionUtils::insert(synonymPair, resultTable[syn1][i], resultTable[syn2][i]);
    }

    return synonymPair;
}

void QueryResult::addSynonymGroup(std::string synonym,
    std::unordered_set<std::string>& valueSet) {
    crossProductSingle(synonym, valueSet);
}

void QueryResult::mergeResult(ClauseResult& clauseResult) {
    if (!clauseResult.isSuccess()) {
        isQuerySuccess = false;
        return;
    }

    std::vector<std::string> clauseSynonyms = clauseResult.getClauseSynonyms();
    std::unordered_map<std::string,
        std::unordered_set<std::string>> clauseResultData = clauseResult.getResultMap();

    if (clauseSynonyms.size() == 1) {
        std::unordered_set<std::string> clauseResultSet;
        CollectionUtils::collapseKey(clauseResultData, clauseResultSet);
        handleSingleMerge(clauseSynonyms[0], clauseResultSet);
    } else if (clauseSynonyms.size() == 2) {
        handleDoubleMerge(clauseSynonyms[0], clauseSynonyms[1], clauseResultData);
    }
}

void QueryResult::mergeResult(QueryResult& otherResult) {
    if (this->synonymList.empty()) {
        this->synonymList = otherResult.synonymList;
        this->resultTable = otherResult.resultTable;
        this->isQuerySuccess = otherResult.isQuerySuccess;
        return;
    }

    QueryResult newResult;

    int curResultTableSize = resultTable.begin()->second.size();
    int newResultTableSize = otherResult.resultTable.begin()->second.size();

    newResult.synonymList = this->synonymList;

    for (auto& syn : otherResult.synonymList) {
        newResult.synonymList.push_back(syn);
    }

    for (int i = 0; i < curResultTableSize; i++) {
        std::vector<std::string> firstEntryValues = getEntryValue(i);

        for (int j = 0; j < newResultTableSize; j++) {
            std::vector<std::string> secondEntryValues = otherResult.getEntryValue(j);

            newResult.addEntry(firstEntryValues, secondEntryValues);
        }
    }

    this->synonymList = newResult.synonymList;
    this->resultTable = newResult.resultTable;
    this->isQuerySuccess = otherResult.isQuerySuccess;
}


void QueryResult::collapseResult(std::unordered_set<std::string>& synonymToKeep) {
    for (int i = synonymList.size() - 1; i >= 0; i--) {
        if (!CollectionUtils::find(synonymToKeep, synonymList[i])) {
            resultTable.erase(synonymList[i]);
            synonymList.erase(synonymList.begin() + i);
        }
    }

    if (!resultTable.empty()) {
        QueryResult newResult;

        newResult.synonymList = this->synonymList;

        std::unordered_set<std::string> tableSet;
        int resultTableSize = resultTable.begin()->second.size();

        for (int i = 0; i < resultTableSize; i++) {
            std::vector<std::string> entryValues = getEntryValue(i);
            newResult.handleAddEntryWithFilter(entryValues, tableSet);
        }

        resultTable = newResult.resultTable;
    }
}

std::unordered_map<std::string, std::vector<std::string>>& QueryResult::getResultMap() {
    return this->resultTable;
}
