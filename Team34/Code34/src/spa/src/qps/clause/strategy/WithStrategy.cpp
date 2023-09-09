// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "WithStrategy.h"
#include <stdexcept>
#include <unordered_set>

void WithStrategy::setArguments(EntityArgument* arg1, EntityArgument* arg2) {
    this->arg1 = arg1;
    this->arg2 = arg2;
}

void WithStrategy::initializeWildcard(std::vector<std::shared_ptr<Argument>>& argumentList,
    DI& di) {}

bool WithStrategy::isClauseHold(const std::string& firstItem, const std::string& secondItem) {
    std::string firstVal = (arg1 != nullptr) ? arg1->getAttrFromPKB(firstItem) : firstItem;
    std::string secondVal = (arg2 != nullptr) ? arg2->getAttrFromPKB(secondItem) : secondItem;

    return firstVal == secondVal;
}

bool WithStrategy::isClauseHold() {
    throw std::runtime_error("With should not have any wildcard");
}

bool WithStrategy::isClauseHoldKey(const std::string& key) {
    throw std::runtime_error("With should not have any wildcard");
}

bool WithStrategy::isClauseHoldValue(const std::string& value) {
    throw std::runtime_error("With should not have any wildcard");
}

bool WithStrategy::initializeItemMap(EntityArgument* arg1, EntityArgument* arg2) {
    setArguments(arg1, arg2);
    std::unordered_set<std::string> arg1Result = arg1->getPKBValueList();
    std::unordered_set<std::string> arg2Result = arg2->getPKBValueList();

    handleCrossProductAddItemMap(arg1Result, arg2Result);
    return false;
}

void WithStrategy::initializeArgument(EntityArgument* arg1, EntityArgument* arg2) {
    setArguments(arg1, arg2);
}

bool WithStrategy::initializeItemMap(EntityArgument* arg1, InputArgument* arg2) {
    setArguments(arg1, nullptr);
    std::unordered_set<std::string> keyResult = arg1->getPKBValueList();
    std::unordered_set<std::string> valueSet = {arg2->getValue()};

    handleCrossProductAddItemMap(keyResult, valueSet);
    return false;
}

bool WithStrategy::initializeItemMap(InputArgument* arg1, EntityArgument* arg2) {
    setArguments(nullptr, arg2);
    std::unordered_set<std::string> valueResult = arg2->getPKBValueList();
    std::unordered_set<std::string> keySet = {arg1->getValue()};

    handleCrossProductAddItemMap(keySet, valueResult);
    return false;
}

void WithStrategy::setPKBInterface(DI& di) {}

WithStrategy::WithStrategy() : ClauseStrategy() {
    this->arg1 = nullptr;
    this->arg2 = nullptr;
}
