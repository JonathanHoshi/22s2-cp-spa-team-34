// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "ConversionUtils.h"

std::unordered_set<std::string>
ConversionUtils::convertIntToStringSet(std::unordered_set<int> intSet) {
    std::unordered_set<std::string> strSet;

    for (int intValue : intSet) {
        strSet.emplace(std::to_string(intValue));
    }

    return strSet;
}

std::unordered_map<std::string, std::string>
ConversionUtils::convertIntToStringMap(std::unordered_map<int, int> intMap) {
    std::unordered_map<std::string, std::string> strMap;

    for (auto& [key, value] : intMap) {
        strMap.emplace(std::to_string(key), std::to_string(value));
    }

    return strMap;
}

std::unordered_map<std::string, std::unordered_set<std::string>>
ConversionUtils::convertIntToStringMapSet(std::unordered_map<int,
    std::unordered_set<int>> intMapSet) {
    std::unordered_map<std::string, std::unordered_set<std::string>> strMapSet;

    for (auto& [key, valueSet] : intMapSet) {
        strMapSet.emplace(std::to_string(key), convertIntToStringSet(valueSet));
    }

    return strMapSet;
}

std::unordered_map<std::string, std::unordered_set<std::string>>
ConversionUtils::convertIntToStringMapSet(std::unordered_map<int,
    std::unordered_set<std::string>> intMapSet) {
    std::unordered_map<std::string, std::unordered_set<std::string>> strMapSet;

    for (auto& [key, valueSet] : intMapSet) {
        strMapSet.emplace(std::to_string(key), valueSet);
    }

    return strMapSet;
}
