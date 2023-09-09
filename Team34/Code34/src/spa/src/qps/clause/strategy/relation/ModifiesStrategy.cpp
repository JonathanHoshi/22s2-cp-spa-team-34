// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.
#include <unordered_set>
#include "ModifiesStrategy.h"
#include "common/ConversionUtils.h"

void ModifiesStrategy::initializeWildcard(std::vector<std::shared_ptr<Argument>>& argumentList,
    DI& di) {
    ClauseStrategyUtils::initializeWildcardRightArgVar(argumentList[1], di);
}

bool ModifiesStrategy::isClauseHold(const std::string& firstItem, const std::string& secondItem) {
    return (this->isProcedure)
        ? pkbInterface->isAssociatedP(firstItem, secondItem)
        : pkbInterface->isAssociatedS(stoi(firstItem), secondItem);
}

bool ModifiesStrategy::isClauseHold() {
    return (this->isProcedure)
        ? pkbInterface->hasAssociatedP()
        : pkbInterface->hasAssociatedS();
}

bool ModifiesStrategy::isClauseHoldKey(const std::string& key) {
    return (this->isProcedure)
        ? pkbInterface->hasAssociatedPByKey(key)
        : pkbInterface->hasAssociatedSByKey(stoi(key));
}

bool ModifiesStrategy::isClauseHoldValue(const std::string& value) {
    return (this->isProcedure)
        ? pkbInterface->hasAssociatedPByValue(value)
        : pkbInterface->hasAssociatedSByValue(value);
}

bool ModifiesStrategy::initializeItemMap(EntityArgument* arg1, EntityArgument* arg2) {
    itemMap = (this->isProcedure)
        ? pkbInterface->getProcVarEntries()
        : ConversionUtils::convertIntToStringMapSet(pkbInterface->getStmtVarEntries());
    return false;
}

bool ModifiesStrategy::initializeItemMap(EntityArgument* arg1, InputArgument* arg2) {
    std::unordered_set<std::string> keyResult = (this->isProcedure)
        ? pkbInterface->getProcsByVar(arg2->getValue())
        : ConversionUtils::convertIntToStringSet(
            pkbInterface->getStmtsByVar(arg2->getValue()));

    std::unordered_set<std::string> valueSet = {arg2->getValue()};

    handleFilterAddCrossProductItemMap(keyResult, valueSet, arg1, nullptr);
    return true;
}

bool ModifiesStrategy::initializeItemMap(InputArgument* arg1, EntityArgument* arg2) {
    std::unordered_set<std::string> valueResult = (this->isProcedure)
        ? pkbInterface->getVarsByProc(arg1->getValue())
        : pkbInterface->getVarsByStmt(stoi(arg1->getValue()));

    std::unordered_set<std::string> keySet = {arg1->getValue()};

    handleCrossProductAddItemMap(keySet, valueResult);
    return true;
}

void ModifiesStrategy::setPKBInterface(DI& di) {
    setPKBInterface(&di.getService<IModifiesGetter>());
}

void ModifiesStrategy::setPKBInterface(IModifiesGetter* pkbInterface) {
    this->pkbInterface = pkbInterface;
}

ModifiesStrategy::ModifiesStrategy() : ModifiesStrategy(false) {}
ModifiesStrategy::ModifiesStrategy(bool isProcedure) : ModifiesStrategy(nullptr, isProcedure) {}
ModifiesStrategy::ModifiesStrategy(IModifiesGetter* pkbInterface) :
    ModifiesStrategy(pkbInterface, false) {}

ModifiesStrategy::ModifiesStrategy(IModifiesGetter* pkbInterface, bool isProcedure) :
    ClauseStrategy() {
    setPKBInterface(pkbInterface);
    this->isProcedure = isProcedure;
}
