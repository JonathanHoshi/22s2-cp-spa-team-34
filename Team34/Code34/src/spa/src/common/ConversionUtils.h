// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once

#include <memory>
#include <string>
#include <unordered_set>
#include <unordered_map>

class ConversionUtils {
public:
    static std::unordered_set<std::string> convertIntToStringSet(std::unordered_set<int> intSet);
    static std::unordered_map<std::string,
        std::string> convertIntToStringMap(std::unordered_map<int, int> intMap);
    static std::unordered_map<std::string, std::unordered_set<std::string>>
        convertIntToStringMapSet(std::unordered_map<int, std::unordered_set<int>> intMapSet);
    static std::unordered_map<std::string, std::unordered_set<std::string>>
        convertIntToStringMapSet(std::unordered_map<int,
            std::unordered_set<std::string>> intMapSet);

private:
    ConversionUtils();
};
