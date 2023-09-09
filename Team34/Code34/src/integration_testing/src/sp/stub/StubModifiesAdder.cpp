#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
#include "common/CollectionUtils.h"
#include "pkb/interfaces/IModifiesAdder.h"



class StubModifiesAdder : public IModifiesAdder {

public:
    std::unordered_map<std::string, std::unordered_set<std::string>> prodModifiesMap;
    std::unordered_map<int, std::unordered_set<std::string>> stmtModifiesMap;

    bool containsModifiesS(const int& stmtNo, const std::string& variable) {
        return CollectionUtils::find(stmtModifiesMap, stmtNo, variable);
    }

    bool containsModifiesP(const std::string& proc, const std::string& variable) {
        return CollectionUtils::find(prodModifiesMap, proc, variable);
    }

    void addVarP(const std::string& procedure, const std::string& variable) override {
        CollectionUtils::insert(prodModifiesMap, procedure, variable);
    }

    void addVarS(const int& statementNo, const std::string& variable) override {
        CollectionUtils::insert(stmtModifiesMap, statementNo, variable);
    }
};