// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once

#include <unordered_map>
#include <unordered_set>
#include <queue>
#include "pkb/base/BaseMapSet.h"
#include "CyclicTTable.h"
#include "pkb/interfaces/INextAdder.h"
#include "pkb/interfaces/INextGetter.h"
#include "pkb/interfaces/INextTClearer.h"

class NextTable : public CyclicTTable, public INextAdder, public INextGetter, public INextTClearer {
private:
    BaseMapSet<int, int> keyToValEntries;    // Store key -> val pairs of Next
    BaseMapSet<int, int> valToKeyEntries;    // Store val -> key pairs of Next
    BaseMapSet<int, int> keyToValTEntries;    // Store key -> val pairs of Next
    BaseMapSet<int, int> valToKeyTEntries;    // Store val -> key pairs of Next
    bool computedAll = false;

    void generateNextT(const int& key, BaseMapSet<int, int>& direction,
        BaseMapSet<int, int>& directionT);

public:
    // Clears the cached T values
    void clearNextT() override;

    /**
     * Add new entry to both frontToBackEntries and backToFrontEntries.
     *
     * @param front The front statement number for the Next relationship.
     * @param back The back statement number for the Next relationship.
     */
    void addNext(const int& front, const int& back) override;

    /**
     * Get the keyToVal entries for Next.
     * @return keyToVal entries for Next.
     */
    std::unordered_map<int, std::unordered_set<int>> getNextEntries() override;

    /**
     * Get the keyToValT entries for Next*
     * @return keyToValT entries for Next*
     */
    std::unordered_map<int, std::unordered_set<int>> getNextTEntries() override;


    /**
     * Check whether Next relationship for two statements holds.
     * @param front the front statement.
     * @param back the back statement.
     * @return whether Next relationship for these two statements holds.
     */
    bool isNext(const int& key, const int& value) override;

    /**
     * Check whether Next* (transitive Next) relationship for two statements holds.
     * @param front the front statement.
     * @param back the back statement.
     * @return whether Next relationship for these two statements holds.
     */
    bool isNextT(const int& key, const int& value) override;

    /**
     * Given a value, get all keys which Next holds for Key->value
     * @param value target value
     * @return All keys which Next holds for Key->value
     */
    std::unordered_set<int> getKeysByValue(const int& value) override;

    /**
     * Given a key, get all values which Next holds for key->value
     * @param key target key
     * @return All values which Next holds for key->value
     */
    std::unordered_set<int> getValuesByKey(const int& key) override;

    /**
     * Given a value, get all keys which Next* holds for key->value
     * @param value target value
     * @return All keys which Next* holds for key->value
     */
    std::unordered_set<int> getTKeysByValue(const int& value) override;

    /**
     * Given a key, get all values which Next* holds for key->value
     * @param key target key
     * @return All values which Next* holds for key->value
     */
    std::unordered_set<int> getTValuesByKey(const int& key) override;

    /**
     * Return whether or not there is Next relationship exists
     * @return whether or not there is Next relationship exists
     */
    bool hasNext() override;

    /**
     * Return whether a key statement have corresponding value statement of Next relationship
     * @param key target key
     * @return whether a key statement have corresponding value statement of Next relationship
     */
    bool hasNextByKey(const int& key) override;

    /**
     * Return whether a value statement have corresponding key statement of Next relationship
     * @param key target value
     * @return whether a value statement have corresponding key statement of Next relationship
     */
    bool hasNextByValue(const int& value) override;
};
