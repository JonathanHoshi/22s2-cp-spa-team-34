// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.
#include <unordered_set>
#include "UsesStrategy.h"
#include "common/ConversionUtils.h"

void UsesStrategy::initializeWildcard(std::vector<std::shared_ptr<Argument>>& argumentList,
    DI& di) {
    ClauseStrategyUtils::initializeWildcardRightArgVar(argumentList[1], di);
}

bool UsesStrategy::isClauseHold(const std::string& firstItem, const std::string& secondItem) {
    return (this->isProcedure)
        ? pkbInterface->isAssociatedP(firstItem, secondItem)
        : pkbInterface->isAssociatedS(stoi(firstItem), secondItem);
}

bool UsesStrategy::isClauseHold() {
    return (this->isProcedure)
        ? pkbInterface->hasAssociatedP()
        : pkbInterface->hasAssociatedS();
}

bool UsesStrategy::isClauseHoldKey(const std::string& key) {
    return (this->isProcedure)
        ? pkbInterface->hasAssociatedPByKey(key)
        : pkbInterface->hasAssociatedSByKey(stoi(key));
}

bool UsesStrategy::isClauseHoldValue(const std::string& value) {
    return (this->isProcedure)
        ? pkbInterface->hasAssociatedPByValue(value)
        : pkbInterface->hasAssociatedSByValue(value);
}

bool UsesStrategy::initializeItemMap(EntityArgument* arg1, EntityArgument* arg2) {
    itemMap = (isProcedure)
        ? pkbInterface->getProcVarEntries()
        : ConversionUtils::convertIntToStringMapSet(pkbInterface->getStmtVarEntries());
    return false;
}

bool UsesStrategy::initializeItemMap(EntityArgument* arg1, InputArgument* arg2) {
    std::unordered_set<std::string> keyResult = (isProcedure)
        ? pkbInterface->getProcsByVar(arg2->getValue())
        : ConversionUtils::
        convertIntToStringSet(pkbInterface->getStmtsByVar(arg2->getValue()));

    std::unordered_set<std::string> valueSet = {arg2->getValue()};

    handleFilterAddCrossProductItemMap(keyResult, valueSet, arg1, nullptr);
    return true;
}

bool UsesStrategy::initializeItemMap(InputArgument* arg1, EntityArgument* arg2) {
    std::unordered_set<std::string> valueResult = (this->isProcedure)
        ? pkbInterface->getVarsByProc(arg1->getValue())
        : pkbInterface->getVarsByStmt(stoi(arg1->getValue()));

    std::unordered_set<std::string> keySet = {arg1->getValue()};

    handleCrossProductAddItemMap(keySet, valueResult);
    return true;
}

void UsesStrategy::setPKBInterface(DI& di) {
    setPKBInterface(&di.getService<IUsesGetter>());
}

void UsesStrategy::setPKBInterface(IUsesGetter* pkbInterface) {
    this->pkbInterface = pkbInterface;
}

UsesStrategy::UsesStrategy() : UsesStrategy(false) {}
UsesStrategy::UsesStrategy(bool isProcedure) : UsesStrategy(nullptr, isProcedure) {}
UsesStrategy::UsesStrategy(IUsesGetter* pkbInterface) :
    UsesStrategy(pkbInterface, false) {}

UsesStrategy::UsesStrategy(IUsesGetter* pkbInterface, bool isProcedure) :
    ClauseStrategy() {
    setPKBInterface(pkbInterface);
    this->isProcedure = isProcedure;
}
