// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once

#include <string>
#include <unordered_set>

/**
 * Template class for a set of entities.
 */
template <typename T> class BaseSet {
private:
    std::unordered_set<T> entries;

public:
    BaseSet();

    /**
     * Gets all entries in the set
     *
     * @return set of unique values
     */
    std::unordered_set<T> getEntries();

    /**
     * Adds an entry to the set
     *
     * @param entry the value to add
     */
    void addEntry(const T& entry);

    /**
     * Checks if the entry exists in the set
     *
     * @param entry the entry to check
     * @return true if exists, else false
     */
    bool containKey(const T& entry);

    /**
     * Gets the number of entries in the set
     *
     * @return number of entries
     */
    size_t getSize();
};

template <typename T> BaseSet<T>::BaseSet() = default;

template <typename T> std::unordered_set<T> BaseSet<T>::getEntries() {
    return this->entries;
}

template <typename T> void BaseSet<T>::addEntry(const T& entry) {
    this->entries.insert(entry);
}

template <typename T> bool BaseSet<T>::containKey(const T& entry) {
    return this->entries.find(entry) != this->entries.end();
}

template <typename T> size_t BaseSet<T>::getSize() {
    return this->entries.size();
}
