// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once

#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <string>

class CollectionUtils {
public:
    // Set Utils
    template <typename K>
    static void merge(std::unordered_set<K>& toSet, std::unordered_set<K>& fromSet);
    template<typename K>
    static bool find(const std::unordered_set<K>& refSet, const K& key);

    // Map Utils
    template <typename K, typename V>
    static bool find(const std::unordered_map<K, V>& refMap, const K& key);
    template <typename K, typename V>
    static bool findValue(const std::unordered_map<K, V>& refMap, const V& value);
    template <typename K, typename V>
    static bool find(const std::unordered_map<K, V>& refMap, const K& key, const V& value);
    template <typename K, typename V>
    static void collapseKey(std::unordered_map<K, V>& refMap, std::unordered_set<K>& toSet);
    template <typename K, typename V>
    static void collapse(std::unordered_map<K, V>& refMap, std::unordered_set<V>& toSet);

    // Map Set Utils
    template <typename K, typename V>
    static void insert(std::unordered_map<K, std::unordered_set<V>>& mapSet,
        K key, V value);
    template <typename K, typename V>
    static void insert(std::unordered_map<K, std::unordered_set<V>>& mapSet, K key,
        std::unordered_set<V>& refSet);
    template <typename K, typename V>
    static void merge(std::unordered_map<K, std::unordered_set<V>>& toMapSet,
        std::unordered_map<K, std::unordered_set<V>>& fromMapSet);
    template <typename K, typename V>
    static void collapseKey(std::unordered_map<K, std::unordered_set<V>>& refMapSet,
        std::unordered_set<K>& toSet);
    template <typename K, typename V>
    static void collapse(std::unordered_map<K, std::unordered_set<V>>& refMapSet,
        std::unordered_set<V>& toSet);
    template <typename K, typename V>
    static void clear(std::unordered_map<K, std::unordered_set<V>>& mapSet);
    template <typename K, typename V>
    static void remove(std::unordered_map<K, std::unordered_set<V>>& mapSet,
        K key, V& value);
    template <typename K, typename V>
    static void remove(std::unordered_map<K, std::unordered_set<V>>& mapSet, K key,
        std::unordered_set<V>& refSet);
    template <typename K, typename V>
    static bool find(const std::unordered_map<K, std::unordered_set<V>>& mapSet,
        const K& key, const V& value);
    template <typename K, typename V>
    static bool find(const std::unordered_map<K, std::unordered_set<V>>& mapSet,
        const K& key);
    template <typename K, typename V>
    static bool findValue(const std::unordered_map<K, std::unordered_set<V>>& mapSet,
        const V& value);
    template <typename K, typename V>
    static void getKeySetByValue(const std::unordered_map<K,
        std::unordered_set<V>>&mapSet, const V& value, std::unordered_set<K>& keySet);
    template <typename K>
    static void popStackIntoSet(std::stack<K>& fromStack, std::unordered_set<K>& set);

    template <typename K, typename V>
    static std::unordered_map<K, std::unordered_set<V>> mapToMapSet(
        std::unordered_map<K, V>& refMap);

private:
    CollectionUtils();
};

template <typename K>
void CollectionUtils::merge(std::unordered_set<K>& toSet,
    std::unordered_set<K>& fromSet) {
    for (auto& value : fromSet) {
        toSet.insert(value);
    }
}


template <typename K>
bool CollectionUtils::find(const std::unordered_set<K>& refSet,
    const K& key) {
    return refSet.find(key) != refSet.end();
}

template <typename K, typename V>
bool CollectionUtils::find(const std::unordered_map<K, V>& refMap,
    const K& key) {
    return refMap.find(key) != refMap.end();
}

template <typename K, typename V>
bool CollectionUtils::findValue(const std::unordered_map<K, V>& refMap,
    const V& value) {
    for (auto& [key, val] : refMap) {
        if (val == value) {
            return true;
        }
    }
    return false;
}

template <typename K, typename V>
bool CollectionUtils::find(const std::unordered_map<K, V>& refMap,
    const K& key, const V& value) {
    return CollectionUtils::find(refMap, key) && refMap.at(key) == value;
}

template <typename K, typename V>
void CollectionUtils::collapseKey(std::unordered_map<K, V>& refMap,
    std::unordered_set<K>& toSet) {
    for (auto& [key, value] : refMap) {
        toSet.insert(key);
    }
}

template <typename K, typename V>
void CollectionUtils::collapse(std::unordered_map<K, V>& refMap,
    std::unordered_set<V>& toSet) {
    for (auto& [key, value] : refMap) {
        toSet.insert(value);
    }
}


template <typename K, typename V>
void CollectionUtils::insert(std::unordered_map<K,
    std::unordered_set<V>>&mapSet, K key, V value) {
    auto itor = mapSet.find(key);
    if (itor == mapSet.end()) {
        std::unordered_set<V> newSet;
        newSet.insert(value);
        mapSet.insert({key, newSet});
    } else {
        std::unordered_set newSet = itor->second;
        newSet.insert(value);
        mapSet.insert_or_assign(key, newSet);
    }
}

template <typename K, typename V>
void CollectionUtils::insert(std::unordered_map<K,
    std::unordered_set<V>>&mapSet, K key,
    std::unordered_set<V>& refSet) {
    auto itor = mapSet.find(key);
    if (itor == mapSet.end()) {
        std::unordered_set<V> newSet;
        newSet.insert(refSet.begin(), refSet.end());
        mapSet.insert({key, newSet});
    } else {
        std::unordered_set newSet = itor->second;
        newSet.insert(refSet.begin(), refSet.end());
        mapSet.insert_or_assign(key, newSet);
    }
}

template <typename K, typename V>
void CollectionUtils::merge(std::unordered_map<K,
    std::unordered_set<V>>&toMapSet, std::unordered_map<K,
    std::unordered_set<V>>&fromMapSet) {
    for (auto& [key, set] : fromMapSet) {
        insert(toMapSet, key, set);
    }
}

template <typename K, typename V>
void CollectionUtils::collapseKey(std::unordered_map<K,
    std::unordered_set<V>>&refMapSet,
    std::unordered_set<K>& toSet) {
    for (auto& [key, set] : refMapSet) {
        toSet.insert(key);
    }
}

template <typename K, typename V>
void CollectionUtils::collapse(std::unordered_map<K,
    std::unordered_set<V>>&refMapSet,
    std::unordered_set<V>& toSet) {
    for (auto& [key, set] : refMapSet) {
        for (const V& value : set)
            toSet.insert(value);
    }
}

template <typename K, typename V>
void CollectionUtils::clear(std::unordered_map<K,
    std::unordered_set<V>>&map) {
    map.clear();
}

template <typename K, typename V>
void CollectionUtils::remove(std::unordered_map<K,
    std::unordered_set<V>>&mapSet,
    K key, V& value) {
    auto itor = mapSet.find(key);
    if (itor != mapSet.end()) {
        mapSet.at(key).erase(value);
    }
}

template <typename K, typename V>
void CollectionUtils::remove(std::unordered_map<K,
    std::unordered_set<V>>&mapSet, K key,
    std::unordered_set<V>& refSet) {
    auto itor = mapSet.find(key);
    if (itor != mapSet.end()) {
        for (std::string value : refSet) {
            mapSet.at(key).erase(value);
        }
    }
}

template <typename K, typename V>
bool CollectionUtils::find(const std::unordered_map<K,
    std::unordered_set<V>>&mapSet,
    const K& key, const V& value) {
    return CollectionUtils::find(mapSet, key)
        && mapSet.at(key).find(value) != mapSet.at(key).end();
}

template <typename K, typename V>
bool CollectionUtils::find(const std::unordered_map<K,
    std::unordered_set<V>>&mapSet,
    const K& key) {
    return mapSet.find(key) != mapSet.end();
}

template <typename K, typename V>
bool CollectionUtils::findValue(const std::unordered_map<K,
    std::unordered_set<V>>&mapSet,
    const V& value) {
    for (auto& [key, valueList] : mapSet) {
        if (valueList.find(value) != valueList.end()) {
            return true;
        }
    }

    return false;
}

template <typename K, typename V>
void CollectionUtils::getKeySetByValue(const std::unordered_map<K,
    std::unordered_set<V>>&mapSet,
    const V& value, std::unordered_set<K>& keySet) {
    for (auto& [key, valueList] : mapSet) {
        if (valueList.find(value) != valueList.end()) {
            keySet.emplace(key);
        }
    }
}

template <typename K>
void CollectionUtils::popStackIntoSet(std::stack<K>& fromStack, std::unordered_set<K>& set) {
    while (!fromStack.empty()) {
        set.insert(fromStack.top());
        fromStack.pop();
    }
}

template<typename K, typename V>
std::unordered_map<K, std::unordered_set<V>>
CollectionUtils::mapToMapSet(std::unordered_map<K, V>& refMap) {
    std::unordered_map<K, std::unordered_set<V>> result;

    for (auto& [key, value] : refMap) {
        insert(result, key, value);
    }

    return result;
}
