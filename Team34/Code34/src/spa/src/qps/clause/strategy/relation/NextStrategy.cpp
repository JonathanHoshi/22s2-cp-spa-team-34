// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.
#include <unordered_set>
#include "NextStrategy.h"
#include "common/ConversionUtils.h"
#include "qps/argument/entity/stmt/StmtStmtEntity.h"

void NextStrategy::initializeWildcard(std::vector<std::shared_ptr<Argument>>& argumentList,
    DI& di) {
    ClauseStrategyUtils::initializeWildcardBothArg(argumentList, false, di);
}

bool NextStrategy::isClauseHold(const std::string& firstItem, const std::string& secondItem) {
    return (this->isTransitive)
        ? pkbInterface->isNextT(stoi(firstItem), stoi(secondItem))
        : pkbInterface->isNext(stoi(firstItem), stoi(secondItem));
}

bool NextStrategy::isClauseHold() {
    return pkbInterface->hasNext();
}

bool NextStrategy::isClauseHoldKey(const std::string& key) {
    return pkbInterface->hasNextByKey(stoi(key));
}

bool NextStrategy::isClauseHoldValue(const std::string& value) {
    return pkbInterface->hasNextByValue(stoi(value));
}

bool NextStrategy::initializeItemMap(EntityArgument* arg1, EntityArgument* arg2) {
    itemMap = (this->isTransitive)
        ? ConversionUtils::convertIntToStringMapSet(pkbInterface->getNextTEntries())
        : ConversionUtils::convertIntToStringMapSet(pkbInterface->getNextEntries());

    bool isBothStmt = StmtStmtEntity::checkType(arg1) && StmtStmtEntity::checkType(arg2);

    return isBothStmt;  // require synonym filtering for specfic statement
}

bool NextStrategy::initializeItemMap(EntityArgument* arg1, InputArgument* arg2) {
    std::unordered_set<std::string> keyResult = (this->isTransitive)
        ? ConversionUtils::
        convertIntToStringSet(pkbInterface->getTKeysByValue(stoi(arg2->getValue())))
        : ConversionUtils::
        convertIntToStringSet(pkbInterface->getKeysByValue(stoi(arg2->getValue())));

    std::unordered_set<std::string> valueSet = {arg2->getValue()};

    handleFilterAddCrossProductItemMap(keyResult, valueSet, arg1, nullptr);
    return true;
}

bool NextStrategy::initializeItemMap(InputArgument* arg1, EntityArgument* arg2) {
    std::unordered_set<std::string> valueResult = (this->isTransitive)
        ? ConversionUtils::
        convertIntToStringSet(pkbInterface->getTValuesByKey(stoi(arg1->getValue())))
        : ConversionUtils::
        convertIntToStringSet(pkbInterface->getValuesByKey(stoi(arg1->getValue())));

    std::unordered_set<std::string> keySet = {arg2->getValue()};

    handleFilterAddCrossProductItemMap(keySet, valueResult, nullptr, arg2);

    return true;
}

void NextStrategy::setPKBInterface(DI& di) {
    setPKBInterface(&di.getService<INextGetter>());
}

void NextStrategy::setPKBInterface(INextGetter* pkbInterface) {
    this->pkbInterface = pkbInterface;
}

NextStrategy::NextStrategy() : NextStrategy(false) {}
NextStrategy::NextStrategy(bool isTransitive) : NextStrategy(nullptr, isTransitive) {}
NextStrategy::NextStrategy(INextGetter* pkbInterface) :
    NextStrategy(pkbInterface, false) {}

NextStrategy::NextStrategy(INextGetter* pkbInterface, bool isTransitive) :
    ClauseStrategy() {
    setPKBInterface(pkbInterface);
    this->isTransitive = isTransitive;
}

int NextStrategy::getPreferenceValue() {
    return NEXT_PREFERENCE_VALUE;
}
