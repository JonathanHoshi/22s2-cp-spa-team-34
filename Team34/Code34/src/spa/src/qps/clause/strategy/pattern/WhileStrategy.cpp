// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.
#include <unordered_set>
#include "WhileStrategy.h"
#include "common/ConversionUtils.h"

void WhileStrategy::initializeWildcard(std::vector<std::shared_ptr<Argument>>& argumentList,
    DI& di) {
    ClauseStrategyUtils::initializeWildcardRightArgVar(argumentList[1], di);
}

bool WhileStrategy::isClauseHold(const std::string& firstItem, const std::string& secondItem) {
    return pkbInterface->isValidPattern(stoi(firstItem), secondItem);
}

bool WhileStrategy::isClauseHold() {
    return pkbInterface->hasValidPattern();
}

bool WhileStrategy::isClauseHoldKey(const std::string& key) {
    throw std::runtime_error("While Pattern is not expecting a IDENT on the left arg");
}

bool WhileStrategy::isClauseHoldValue(const std::string& value) {
    return pkbInterface->hasValidPattern(value);
}

bool WhileStrategy::initializeItemMap(EntityArgument* arg1, EntityArgument* arg2) {
    itemMap = ConversionUtils::convertIntToStringMapSet(pkbInterface->getStmtVarEntries());
    return true;
}

bool WhileStrategy::initializeItemMap(EntityArgument* arg1, InputArgument* arg2) {
    std::unordered_set<std::string> keyResult =
        ConversionUtils::convertIntToStringSet(pkbInterface->getStmtsByVar(arg2->getValue()));
    std::unordered_set<std::string> valueSet = {arg2->getValue()};

    handleCrossProductAddItemMap(keyResult, valueSet);
    return true;
}

bool WhileStrategy::initializeItemMap(InputArgument* arg1, EntityArgument* arg2) {
    throw std::runtime_error("While Pattern is not expecting a IDENT on the left arg");
}

void WhileStrategy::setPKBInterface(DI& di) {
    setPKBInterface(&di.getService<IWhilePatternGetter>());
}

void WhileStrategy::setPKBInterface(IWhilePatternGetter* pkbInterface) {
    this->pkbInterface = pkbInterface;
}

WhileStrategy::WhileStrategy() : WhileStrategy(nullptr) {}
WhileStrategy::WhileStrategy(IWhilePatternGetter* pkbInterface) : ClauseStrategy() {
    setPKBInterface(pkbInterface);
}
