// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.
#include <unordered_map>
#include <unordered_set>
#include "CallsStrategy.h"

void CallsStrategy::initializeWildcard(std::vector<std::shared_ptr<Argument>>& argumentList,
    DI& di) {
    ClauseStrategyUtils::initializeWildcardBothArg(argumentList, true, di);
}

bool CallsStrategy::isClauseHold(const std::string& firstItem, const std::string& secondItem) {
    return (this->isTransitive)
        ? pkbInterface->isCallsT(firstItem, secondItem)
        : pkbInterface->isCalls(firstItem, secondItem);
}

bool CallsStrategy::isClauseHold() {
    return pkbInterface->hasCalls();
}

bool CallsStrategy::isClauseHoldKey(const std::string& key) {
    return pkbInterface->hasCallsByKey(key);
}

bool CallsStrategy::isClauseHoldValue(const std::string& value) {
    return pkbInterface->hasCallsByValue(value);
}

bool CallsStrategy::initializeItemMap(EntityArgument* arg1, EntityArgument* arg2) {
    std::unordered_map<std::string, std::unordered_set<std::string>> mapResult =
        (this->isTransitive)
        ? pkbInterface->getCallsTEntries()
        : pkbInterface->getCallsEntries();

    itemMap = mapResult;
    return true;
}

bool CallsStrategy::initializeItemMap(EntityArgument* arg1, InputArgument* arg2) {
    std::unordered_set<std::string> keyResult = (this->isTransitive)
        ? pkbInterface->getProcsCallingT(arg2->getValue())
        : pkbInterface->getProcsCalling(arg2->getValue());

    std::unordered_set<std::string> valueSet = {arg2->getValue()};

    handleCrossProductAddItemMap(keyResult, valueSet);
    return true;
}

bool CallsStrategy::initializeItemMap(InputArgument* arg1, EntityArgument* arg2) {
    std::unordered_set<std::string> valueResult = (this->isTransitive)
        ? pkbInterface->getProcsCalledTBy(arg1->getValue())
        : pkbInterface->getProcsCalledBy(arg1->getValue());

    std::unordered_set<std::string> keySet = {arg1->getValue()};

    handleCrossProductAddItemMap(keySet, valueResult);
    return true;
}

void CallsStrategy::setPKBInterface(DI& di) {
    setPKBInterface(&di.getService<ICallsGetter>());
}

void CallsStrategy::setPKBInterface(ICallsGetter* pkbInterface) {
    this->pkbInterface = pkbInterface;
}

CallsStrategy::CallsStrategy() : CallsStrategy(false) {}
CallsStrategy::CallsStrategy(bool isTransitive) : CallsStrategy(nullptr, isTransitive) {}
CallsStrategy::CallsStrategy(ICallsGetter* pkbInterface) : CallsStrategy(pkbInterface, false) {}

CallsStrategy::CallsStrategy(ICallsGetter* pkbInterface, bool isTransitive) : ClauseStrategy() {
    setPKBInterface(pkbInterface);
    this->isTransitive = isTransitive;
}
