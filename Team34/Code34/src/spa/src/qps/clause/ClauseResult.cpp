// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "ClauseResult.h"
#include "common/CollectionUtils.h"

ClauseResult::ClauseResult() {
    this->isClauseSuccess = false;
}

void ClauseResult::initializeSynonym(std::string synonym) {
    this->clauseSynonym.push_back(synonym);
}

void ClauseResult::initializeSynonym(std::string synonym1, std::string synonym2) {
    this->clauseSynonym.push_back(synonym1);
    this->clauseSynonym.push_back(synonym2);
}

void ClauseResult::addEntry(std::string value) {
    if (resultTable.find(value) == resultTable.end()) {
        this->resultTable.emplace(value, std::unordered_set<std::string>());
    }
}

void ClauseResult::addEntry(std::string value1, std::string value2) {
    CollectionUtils::insert(this->resultTable, value1, value2);
}

void ClauseResult::addMap(std::unordered_map<std::string,
    std::unordered_set<std::string>>& resultTable) {
    this->resultTable = resultTable;
}

void ClauseResult::setClausePass() {
    this->isClauseSuccess = true;
}

bool ClauseResult::isSuccess() {
    return this->isClauseSuccess;
}

void ClauseResult::clear() {
    this->clauseSynonym.clear();
    this->resultTable.clear();
    this->isClauseSuccess = false;
}

std::vector<std::string>& ClauseResult::getClauseSynonyms() {
    return this->clauseSynonym;
}

std::unordered_map<std::string, std::unordered_set<std::string>>& ClauseResult::getResultMap() {
    return this->resultTable;
}
