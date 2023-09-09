#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "common/CollectionUtils.h"
#include "pkb/interfaces/INextGetter.h"

using namespace std;

class StubNextGetter : public INextGetter
{
private:
    unordered_map<int, unordered_set<int>> nextEntries;
    unordered_map<int, unordered_set<int>> reverseNextEntries;
    unordered_map<int, unordered_set<int>> nextTEntries;
    unordered_map<int, unordered_set<int>> reverseNextTEntries;

public:
    void setNextEntries(unordered_map<int, unordered_set<int>>& nextEntries) {
        this->nextEntries = nextEntries;
        reverseNextEntries.clear();

        for (auto& [key, valueSet] : nextEntries)
        {
            for (auto& value : valueSet)
            {
                CollectionUtils::insert(reverseNextEntries, value, key);
            }
        }
    }

    void setNextTEntries(unordered_map<int, unordered_set<int>>& nextTEntries)
    {
        this->nextTEntries = nextTEntries;
        reverseNextTEntries.clear();

        for (auto& [key, valueSet] : nextTEntries)
        {
            for (auto& value : valueSet)
            {
                CollectionUtils::insert(reverseNextTEntries, value, key);
            }
        }
    }

    virtual bool isNext(const int& prevStmt, const int& nextStmt) override
    {
        return CollectionUtils::find(nextEntries, prevStmt, nextStmt);
    }

    virtual bool isNextT(const int& prevStmt, const int& nextStmt) override
    {
        return CollectionUtils::find(nextTEntries, prevStmt, nextStmt);
    }

    virtual bool hasNext() override
    {
        return !nextEntries.empty();
    }

    virtual bool hasNextByKey(const int& prevStmt) override
    {
        return CollectionUtils::find(nextEntries, prevStmt);
    }

    virtual bool hasNextByValue(const int& nextStmt) override
    {
        return CollectionUtils::find(reverseNextEntries, nextStmt);
    }

    virtual unordered_map<int, unordered_set<int>> getNextEntries() override
    {
        return nextEntries;
    }

    virtual unordered_map<int, unordered_set<int>> getNextTEntries() override
    {
        return nextTEntries;
    }

    virtual unordered_set<int> getKeysByValue(const int& nextStmt) override
    {
        return (hasNextByValue(nextStmt))
            ? reverseNextEntries[nextStmt]
            : unordered_set<int>();

    }

    virtual unordered_set<int> getValuesByKey(const int& prevStmt) override
    {
        return (hasNextByKey(prevStmt))
            ? nextEntries[prevStmt]
            : unordered_set<int>();
    }

    virtual unordered_set<int> getTKeysByValue(const int& nextStmt) override
    {
        return (hasNextByValue(nextStmt))
            ? reverseNextTEntries[nextStmt]
            : unordered_set<int>();
    }

    virtual unordered_set<int> getTValuesByKey(const int& prevStmt) override
    {
        return (hasNextByKey(prevStmt))
            ? nextTEntries[prevStmt]
            : unordered_set<int>();
    }
};
