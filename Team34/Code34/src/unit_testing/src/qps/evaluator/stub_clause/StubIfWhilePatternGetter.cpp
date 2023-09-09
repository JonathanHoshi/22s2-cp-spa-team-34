#pragma once

#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "common/CollectionUtils.h"
#include "pkb/interfaces/IIfPatternGetter.h"
#include "pkb/interfaces/IWhilePatternGetter.h"



class StubIfWhilePatternGetter : public IIfPatternGetter, public IWhilePatternGetter
{
private:
    std::unordered_map<int, std::unordered_set<std::string>> patternEntries;
    std::unordered_map<std::string, std::unordered_set<int>> reversePatternEntries;

public:
    void setPatternEntries(std::unordered_map<int, std::unordered_set<std::string>>& patternEntries) 
    {
        this->patternEntries = patternEntries;

        for (auto& [key, valueSet] : patternEntries)
        {
            for (auto& value : valueSet)
            {
                CollectionUtils::insert(reversePatternEntries, value, key);
            }
        }
    }

    virtual std::unordered_map<int, std::unordered_set<std::string>> getStmtVarEntries() override
    {
        return this->patternEntries;
    }

    virtual std::unordered_set<std::string> getVarsByStmt(const int& stmtNum) override
    {
        return hasValidPattern(stmtNum) 
            ? patternEntries[stmtNum] 
            : std::unordered_set<std::string>();
    }

    virtual std::unordered_set<int> getStmtsByVar(const std::string& varName) override
    {
        return hasValidPattern(varName)
            ? reversePatternEntries[varName]
            : std::unordered_set<int>();
    }
    virtual bool isValidPattern(const int& stmtNum, const std::string& varName) override
    {
        return CollectionUtils::find(patternEntries, stmtNum, varName);
    }
    virtual bool hasValidPattern() override
    {
        return !patternEntries.empty();
    }
    virtual bool hasValidPattern(const int& stmtNum) override
    {
        return CollectionUtils::find(patternEntries, stmtNum);
    }
    virtual bool hasValidPattern(const std::string& varName) override
    {
        return CollectionUtils::find(reversePatternEntries, varName);
    }
};
