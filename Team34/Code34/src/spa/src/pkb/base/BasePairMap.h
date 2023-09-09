// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once
#include <utility>
#include "unordered_map"

template <typename K, typename L, typename R>

class BasePairMap {
private:
    std::unordered_map<K, std::pair<L, R>> entries;

public:
    /**
     * Constructor of BasePairMap
     */
    BasePairMap();

    /**
     * Return entries
     * @return entries
     */
    std::unordered_map<K, std::pair<L, R>> getEntries();

    /**
     * Get the entry which corresponds to the given key
     * @param key the given key
     * @return the entry value which corresponds to the given key
     */
    std::pair<L, R> getValByKey(K key);

    /**
     * Add new entry to the map
     * @param key the key of the new entry
     * @param val the value of the new entry
     */
    void addEntry(K key, std::pair<L, R> val);

    /**
     * Add new entry to the map
     * @param key the key of the new entry
     * @param leftVal the left val of the std::pair
     * @param rightVal the right val of the std::pair
     */
    void addEntry(K key, L leftVal, R rightVal);

    /**
     * Get size of the map
     * @return the size of the map
     */
    int getSize();

    /**
     * Test whether the map contains a key
     * @param key the searching key
     * @return whether the map contains a key
     */
    bool containKey(K key);
};

template <typename K, typename L, typename R>
BasePairMap<K, L, R>::BasePairMap() = default;

template <typename K, typename L, typename R>
std::unordered_map<K, std::pair<L, R>> BasePairMap<K, L, R>::getEntries() {
    return entries;
}

template <typename K, typename L, typename R>
std::pair<L, R> BasePairMap<K, L, R>::getValByKey(K key) {
    if (entries.count(key)) {
        return entries.at(key);
    } else {
        return std::pair<L, R>();
    }
}

template <typename K, typename L, typename R>
void BasePairMap<K, L, R>::addEntry(K key, std::pair<L, R> val) {
    entries.insert({key, val});
}

template <typename K, typename L, typename R>
void BasePairMap<K, L, R>::addEntry(K key, L leftVal, R rightVal) {
    std::pair<L, R> val{leftVal, rightVal};
    entries.insert({key, val});
}

template <typename K, typename L, typename R>
int BasePairMap<K, L, R>::getSize() {
    return entries.size();
}

template <typename K, typename L, typename R>
bool BasePairMap<K, L, R>::containKey(K key) {
    return entries.count(key) != 0;
}
