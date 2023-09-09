// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once

#include <unordered_map>
#include <unordered_set>

/**
 * Template class for a map of entities (key-set_of_values entities).
 */
template <typename K, typename V> class BaseMapSet {
private:
    std::unordered_map<K, std::unordered_set<V>> entries;

public:
    BaseMapSet();
    /**
     * Gets all entries in the map
     *
     * @return map of key-value entries
     */
    std::unordered_map<K, std::unordered_set<V>> getEntries();

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
    std::unordered_set<V> getValuesByKey(const K& key);

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
BaseMapSet<K, V>::BaseMapSet() = default;

template <typename K, typename V>
std::unordered_map<K, std::unordered_set<V>> BaseMapSet<K, V>::getEntries() {
    return this->entries;
}

template <typename K, typename V>
std::unordered_set<K> BaseMapSet<K, V>::getKeys() {
    std::unordered_set<K> keys;
    for (const auto& kv : this->entries) {
        keys.insert(kv.first);
    }
    return keys;
}

template <typename K, typename V>
std::unordered_set<V> BaseMapSet<K, V>::getValuesByKey(const K& key) {
    auto it = this->entries.find(key);
    if (it == this->entries.end()) {
        return std::unordered_set<V>();
    }
    return it->second;
}

template <typename K, typename V>
bool BaseMapSet<K, V>::hasKey(const K& key) {
    // All elements in a map container are unique
    // Count == 1 means element found
    // http://www.cplusplus.com/reference/map/map/count
    return this->entries.count(key) == 1;
}

template <typename K, typename V>
bool BaseMapSet<K, V>::hasKeyValue(const K& key, const V& value) {
    if (!hasKey(key)) {
        return false;
    }
    return this->getValuesByKey(key).count(value) == 1;
}

template <typename K, typename V>
void BaseMapSet<K, V>::addEntry(const K& key, const V& value) {
    if (!hasKey(key)) {
        // Key does not exist yet, add new <K, std::unordered_set<V>> std::pair
        this->entries.insert({key, std::unordered_set<V>({value})});
    } else if (!hasKeyValue(key, value)) {
        // Key exists but value does not, add new V to K
        std::unordered_set<V>* values = &entries[key];
        values->insert(value);
    } else {
    }
}

template <typename K, typename V>
size_t BaseMapSet<K, V>::getSize() {
    return this->entries.size();
}
