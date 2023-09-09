#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "common/CollectionUtils.h"
#include "pkb/interfaces/IAffectsGetter.h"

using namespace std;

class StubAffectsGetter : public IAffectsGetter
{
private:
    unordered_map<int, unordered_set<int>> affectsEntries;
    unordered_map<int, unordered_set<int>> reverseAffectsEntries;
    unordered_map<int, unordered_set<int>> affectsTEntries;
    unordered_map<int, unordered_set<int>> reverseAffectsTEntries;

public:
    void setAffectsEntries(unordered_map<int, unordered_set<int>>& affectsEntries)
    {
        this->affectsEntries = affectsEntries;
        reverseAffectsEntries.clear();

        for (auto& [key, valueSet] : affectsEntries)
        {
            for (auto& value : valueSet)
            {
                CollectionUtils::insert(reverseAffectsEntries, value, key);
            }
        }
    }

    void setAffectsTEntries(unordered_map<int, unordered_set<int>>& affectsTEntries)
    {
        this->affectsTEntries = affectsTEntries;
        reverseAffectsTEntries.clear();

        for (auto& [key, valueSet] : affectsTEntries)
        {
            for (auto& value : valueSet)
            {
                CollectionUtils::insert(reverseAffectsTEntries, value, key);
            }
        }
    }

    virtual bool isAffects(const int& keyStmt, const int& affectedStmt) override
    {
        return CollectionUtils::find(affectsEntries, keyStmt, affectedStmt);
    }

    virtual bool isAffectsT(const int& keyStmt, const int& affectedStmt) override
    {
        return CollectionUtils::find(affectsTEntries, keyStmt, affectedStmt);
    }

    virtual bool hasAffects() override
    {
        return !affectsEntries.empty();
    }

    virtual bool hasAffectsByKeyStmt(const int& keyStmt) override
    {
        return CollectionUtils::find(affectsEntries, keyStmt);
    }

    virtual bool hasAffectsByAffectedStmt(const int& affectedStmt) override
    {
        return CollectionUtils::find(reverseAffectsEntries, affectedStmt);
    }

    virtual unordered_map<int, unordered_set<int>> getAffectsEntries() override
    {
        return affectsEntries;
    }

    virtual unordered_map<int, unordered_set<int>> getAffectsTEntries() override
    {
        return affectsTEntries;
    }

    virtual unordered_set<int> getKeyStmtsByAffectedStmt(const int& affectedStmt) override
    {
        return (hasAffectsByAffectedStmt(affectedStmt))
            ? reverseAffectsEntries[affectedStmt]
            : unordered_set<int>();

    }

    virtual unordered_set<int> getAffectedStmtsByKeyStmt(const int& keyStmt) override
    {
        return (hasAffectsByKeyStmt(keyStmt))
            ? affectsEntries[keyStmt]
            : unordered_set<int>();
    }

    virtual unordered_set<int> getTKeyStmtsByAffectedStmt(const int& affectedStmt) override
    {
        return (hasAffectsByAffectedStmt(affectedStmt))
            ? reverseAffectsTEntries[affectedStmt]
            : unordered_set<int>();
    }

    virtual unordered_set<int> getTAffectedStmtsByKeyStmt(const int& keyStmt) override
    {
        return (hasAffectsByKeyStmt(keyStmt))
            ? affectsTEntries[keyStmt]
            : unordered_set<int>();
    }
};
