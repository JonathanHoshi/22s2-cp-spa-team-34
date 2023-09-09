#pragma once

#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "common/CollectionUtils.h"
#include "pkb/interfaces/IFollowsGetter.h"



class StubFollowsGetter : public IFollowsGetter
{
private:
    std::unordered_map<int, int> followsEntries;
    std::unordered_map<int, int> reverseFollowsEntries;
    std::unordered_map<int, std::unordered_set<int>> followsTEntries;
    std::unordered_map<int, std::unordered_set<int>> reverseFollowsTEntries;

public:
    void setFollowsEntries(std::unordered_map<int, int>& followsEntries) {
        this->followsEntries = followsEntries;

        for (auto& [key, value] : followsEntries)
        {
            reverseFollowsEntries.emplace(value, key);
        }
    }

    void setFollowsTEntries(std::unordered_map<int, std::unordered_set<int>>& followsTEntries) {
        this->followsTEntries = followsTEntries;

        for (auto& [key, valueSet] : followsTEntries)
        {
            for (auto& value : valueSet)
            {
                CollectionUtils::insert(reverseFollowsTEntries, value, key);
            }
        }
    }

    virtual std::unordered_map<int, int> getFollowsEntries() override
    {
        return this->followsEntries;
    }

    virtual std::unordered_set<int> getBeforeStmts() override
    {
        std::unordered_set<int> keys;
        for (auto& [key, v] : this->followsEntries) {
            keys.insert(key);
        }
        return keys;
    }

    virtual std::unordered_set<int> getAfterStmts() override
    {
        std::unordered_set<int> keys;
        for (auto& [key, v] : this->reverseFollowsEntries) {
            keys.insert(key);
        }
        return keys;
    }

    virtual int getStmtAfter(const int& stmtNum) override
    {
        return hasAssociatedByKey(stmtNum)
            ? followsEntries[stmtNum] 
            : -1;
    }

    virtual int getStmtBefore(const int& stmtNum) override
    {
        return hasAssociatedByValue(stmtNum)
            ? reverseFollowsEntries[stmtNum]
            : -1;
    }

    virtual bool isAssociated(const int& beforeStmt, const int& afterStmt) override
    {
        return CollectionUtils::find(followsEntries, beforeStmt, afterStmt);
    }

    virtual bool hasAssociated() override {
        return !followsEntries.empty();
    }

    virtual bool hasAssociatedByKey(const int& beforeStmt) override {
        return CollectionUtils::find(followsEntries, beforeStmt);
    }

    virtual bool hasAssociatedByValue(const int& afterStmt) override {
        return CollectionUtils::findValue(followsEntries, afterStmt);
    }

    virtual std::unordered_map<int, std::unordered_set<int>> getTEntries() override
    {
        return this->followsTEntries;
    }

    virtual std::unordered_set<int> getTStmtsByKey(const int& stmtNum) override
    {
        return followsTEntries[stmtNum];
    }

    virtual std::unordered_set<int> getTStmtsByValue(const int& stmtNum) override
    {
        return reverseFollowsTEntries[stmtNum];
    }

    virtual bool isAssociatedT(const int& beforeStmt, const int& afterStmt) override {
        return CollectionUtils::find(followsTEntries, beforeStmt, afterStmt);
    }

    virtual bool hasAssociatedT() override {
        return !followsEntries.empty();
    }

    virtual bool hasAssociatedTByKey(const int& beforeStmt) override {
        return CollectionUtils::find(followsTEntries, beforeStmt);
    }

    virtual bool hasAssociatedTByValue(const int& afterStmt) override {
        return CollectionUtils::findValue(followsTEntries, afterStmt);
    }
};
