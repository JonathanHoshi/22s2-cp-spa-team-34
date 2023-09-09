#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "common/CollectionUtils.h"
#include "pkb/interfaces/IParentGetter.h"



class StubParentGetter : public IParentGetter
{
private:
    std::unordered_map<int, std::unordered_set<int>> parentEntries;
    std::unordered_map<int, int> reverseParentEntries;
    std::unordered_map<int, std::unordered_set<int>> parentTEntries;
    std::unordered_map<int, std::unordered_set<int>> reverseParentTEntries;

public:
    void setParentEntries(std::unordered_map<int, std::unordered_set<int>>& parentEntries)
    {
        this->parentEntries = parentEntries;
        reverseParentEntries.clear();

        for (auto& [key, valueSet] : parentEntries)
        {
            for (auto& value : valueSet)
            {
                reverseParentEntries.emplace(value, key);
            }
        }
    }

    void setParentTEntries(std::unordered_map<int, std::unordered_set<int>>& parentTEntries)
    {
        this->parentTEntries = parentTEntries;
        reverseParentTEntries.clear();

        for (auto& [key, valueSet] : parentTEntries)
        {
            for (auto& value : valueSet)
            {
                CollectionUtils::insert(reverseParentTEntries, value, key);
            }
        }
    }

    virtual std::unordered_map<int, std::unordered_set<int>> getParentEntries() override
    {
        return this->parentEntries;
    }

    virtual std::unordered_set<int> getParents() override
    {
        std::unordered_set<int> result;
        CollectionUtils::collapseKey(parentEntries, result);
        return result;
    }

    virtual std::unordered_set<int> getChildren() override
    {
        std::unordered_set<int> result;
        CollectionUtils::collapse(parentEntries, result);
        return result;
    }

    virtual std::unordered_set<int> getChildrenOf(const int& parentStmt) override
    {
        return hasAssociatedByKey(parentStmt)
            ? parentEntries[parentStmt]
            : std::unordered_set<int>();
    }

    virtual int getParentOf(const int& childStmt) override
    {
        return hasAssociatedByValue(childStmt)
            ? reverseParentEntries[childStmt]
            : 0;
    }

    virtual bool isAssociated(const int& parentStmt, const int& childStmt) override
    {
        return CollectionUtils::find(reverseParentEntries, childStmt, parentStmt);
    }

    virtual bool hasAssociated() override
    {
        return !parentEntries.empty();
    }

    virtual bool hasAssociatedByKey(const int& parentStmt) override
    {
        return CollectionUtils::find(parentEntries, parentStmt);
    }

    virtual bool hasAssociatedByValue(const int& childStmt) override
    {
        return CollectionUtils::find(reverseParentEntries, childStmt);
    }

    virtual std::unordered_map<int, std::unordered_set<int>> getTEntries() override
    {
        return this->parentTEntries;
    }

    virtual std::unordered_set<int> getTStmtsByKey(const int& parentStmt) override
    {
        return parentTEntries[parentStmt];
    }

    virtual std::unordered_set<int> getTStmtsByValue(const int& childStmt) override
    {
        return reverseParentTEntries[childStmt];
    }

    virtual bool isAssociatedT(const int& parentStmt, const int& childStmt) override
    {
        return CollectionUtils::find(reverseParentTEntries, childStmt, parentStmt);
    }

    virtual bool hasAssociatedT() override
    {
        return !parentTEntries.empty();
    }

    virtual bool hasAssociatedTByKey(const int& parentStmt) override
    {
        return CollectionUtils::find(parentTEntries, parentStmt);
    }

    virtual bool hasAssociatedTByValue(const int& childStmt) override
    {
        return CollectionUtils::find(reverseParentTEntries, childStmt);
    }
};
