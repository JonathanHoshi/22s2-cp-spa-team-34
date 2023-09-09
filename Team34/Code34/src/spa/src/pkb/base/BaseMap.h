// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once

#include <unordered_map>
#include <unordered_set>

/**
 * Template class for a map of entities (key-value entities).
 */
template <typename K, typename V> class BaseMap {
private:
    std::unordered_map<K, V> entries;

public:
    BaseMap();
    /**
     * Gets all entries in the map
     *
     * @return map of key-value entries
     */
    std::unordered_map<K, V> getEntries();

    /**
     * Gets all keys in the map
     *
     * @return Set of key entries
     */
    std::unordered_set<K> getKeys();

    /**
     * Gets the value that belongs to the key
     *
     * @param key the target key
     * @return the values corresponding to the key
     */
    V getValueByKey(const K& key);

    /**
     * Checks if the map contains the specified key
     *
     * @param key the key to check
     * @return true if it exists, else false
     */
    bool hasKey(const K& key);

    /**
     * Checks if the map contains the specified key-value pair
     *
     * @param key the key to check
     * @param value the value to check
     * @return true if it exists, else false
     */
    bool hasKeyValue(const K& key, const V& value);

    /**
     * Adds an entry to the map
     *
     * @param key the unique key of the entry
     * @param value the value corresponding to the key
     */
    void addEntry(const K& key, const V& value);

    /**
     * Gets the number of entries in the map
     *
     * @return number of entries
     */
    size_t getSize();
};

template <typename K, typename V>
BaseMap<K, V>::BaseMap() = default;

template <typename K, typename V>
std::unordered_map<K, V> BaseMap<K, V>::getEntries() {
    return this->entries;
}

template <typename K, typename V>
std::unordered_set<K> BaseMap<K, V>::getKeys() {
    std::unordered_set<K> keys;
    for (const auto& kv : this->entries) {
        keys.insert(kv.first);
    }
    return keys;
}

template <typename K, typename V>
V BaseMap<K, V>::getValueByKey(const K& key) {
    auto it = this->entries.find(key);
    if (it == this->entries.end()) {
        return {};
    }
    return it->second;
}

template <typename K, typename V>
bool BaseMap<K, V>::hasKey(const K& key) {
    // All elements in a map container are unique
    // Count == 1 means element found
    // http://www.cplusplus.com/reference/map/map/count
    return this->entries.count(key) == 1;
}

template <typename K, typename V>
bool BaseMap<K, V>::hasKeyValue(const K& key, const V& value) {
    if (!hasKey(key)) {
        return false;
    }
    return this->getValueByKey(key) == value;
}

template <typename K, typename V>
void BaseMap<K, V>::addEntry(const K& key, const V& value) {
    this->entries.insert({key, value});
}

template <typename K, typename V>
size_t BaseMap<K, V>::getSize() {
    return this->entries.size();
}
