// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.
#include <unordered_set>
#include "IfStrategy.h"
#include "common/ConversionUtils.h"

void IfStrategy::initializeWildcard(std::vector<std::shared_ptr<Argument>>& argumentList,
    DI& di) {
    ClauseStrategyUtils::initializeWildcardRightArgVar(argumentList[1], di);
}

bool IfStrategy::isClauseHold(const std::string& firstItem,
    const std::string& secondItem) {
    return pkbInterface->isValidPattern(stoi(firstItem), secondItem);
}

bool IfStrategy::isClauseHold() {
    return pkbInterface->hasValidPattern();
}

bool IfStrategy::isClauseHoldKey(const std::string& key) {
    throw std::runtime_error("If Pattern is not expecting a IDENT on the left arg");
}

bool IfStrategy::isClauseHoldValue(const std::string& value) {
    return pkbInterface->hasValidPattern(value);
}

bool IfStrategy::initializeItemMap(EntityArgument* arg1, EntityArgument* arg2) {
    itemMap = ConversionUtils::convertIntToStringMapSet(pkbInterface->getStmtVarEntries());
    return true;
}

bool IfStrategy::initializeItemMap(EntityArgument* arg1, InputArgument* arg2) {
    std::unordered_set<std::string> keyResult =
        ConversionUtils::convertIntToStringSet(pkbInterface->getStmtsByVar(arg2->getValue()));
    std::unordered_set<std::string> valueSet = {arg2->getValue()};

    handleCrossProductAddItemMap(keyResult, valueSet);
    return true;
}

bool IfStrategy::initializeItemMap(InputArgument* arg1, EntityArgument* arg2) {
    throw std::runtime_error("If Pattern is not expecting a IDENT on the left arg");
}

void IfStrategy::setPKBInterface(DI& di) {
    setPKBInterface(&di.getService<IIfPatternGetter>());
}

void IfStrategy::setPKBInterface(IIfPatternGetter* pkbInterface) {
    this->pkbInterface = pkbInterface;
}

IfStrategy::IfStrategy() : IfStrategy(nullptr) {}
IfStrategy::IfStrategy(IIfPatternGetter* pkbInterface) : ClauseStrategy() {
    setPKBInterface(pkbInterface);
}
