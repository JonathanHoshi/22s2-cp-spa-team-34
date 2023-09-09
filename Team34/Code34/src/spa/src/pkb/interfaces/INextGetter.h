// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
#include "di/IService.h"

class INextGetter : public virtual IService {
public:
    ~INextGetter() override = default;

    virtual bool isNext(const int& front, const int& back) = 0;
    virtual bool isNextT(const int& front, const int& back) = 0;

    virtual bool hasNext() = 0;
    virtual bool hasNextByKey(const int& key) = 0;
    virtual bool hasNextByValue(const int& val) = 0;
    virtual std::unordered_map<int, std::unordered_set<int>> getNextEntries() = 0;
    virtual std::unordered_map<int, std::unordered_set<int>> getNextTEntries() = 0;

    virtual std::unordered_set<int> getKeysByValue(const int& value) = 0;
    virtual std::unordered_set<int> getValuesByKey(const int& key) = 0;
    virtual std::unordered_set<int> getTKeysByValue(const int& value) = 0;
    virtual std::unordered_set<int> getTValuesByKey(const int& key) = 0;
};
