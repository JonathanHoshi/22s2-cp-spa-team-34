#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
#include "common/CollectionUtils.h"
#include "pkb/interfaces/IUsesAdder.h"



class StubUsesAdder : public IUsesAdder {

public:
    std::unordered_map<std::string, std::unordered_set<std::string>> prodUsesMap;
    std::unordered_map<int, std::unordered_set<std::string>> stmtUsesMap;

    void addVarS(const int& statementNo, const std::string& variable) override {
        CollectionUtils::insert(stmtUsesMap, statementNo, variable);
    }

    void addVarP(const std::string& procedure, const std::string& variable) override {
        CollectionUtils::insert(prodUsesMap, procedure, variable);
    }

    bool containsUsesS(const int& stmtNo, const std::string& variable) {
        return CollectionUtils::find(stmtUsesMap, stmtNo, variable);
    }

    bool containsUsesP(const std::string& proc, const std::string& variable) {
        return CollectionUtils::find(prodUsesMap, proc, variable);
    }
};