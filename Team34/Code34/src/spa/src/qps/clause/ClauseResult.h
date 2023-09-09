// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class ClauseResult {
private:
    std::unordered_map<std::string, std::unordered_set<std::string>> resultTable;
    std::vector<std::string> clauseSynonym;
    bool isClauseSuccess;

public:
    ClauseResult();

    void initializeSynonym(std::string synonym);
    void initializeSynonym(std::string synonym1, std::string synonym2);

    void addEntry(std::string value);
    void addEntry(std::string value1, std::string value2);
    void addMap(std::unordered_map<std::string, std::unordered_set<std::string>>& resultTable);
    void setClausePass();
    void clear();

    bool isSuccess();
    std::vector<std::string>& getClauseSynonyms();
    std::unordered_map<std::string, std::unordered_set<std::string>>& getResultMap();
};
