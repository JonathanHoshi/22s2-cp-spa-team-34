// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.
#include <unordered_set>
#include <unordered_map>
#include "FollowsStrategy.h"
#include "common/CollectionUtils.h"
#include "common/ConversionUtils.h"
#include "qps/argument/entity/stmt/StmtStmtEntity.h"

void FollowsStrategy::initializeWildcard(std::vector<std::shared_ptr<Argument>>& argumentList,
    DI& di) {
    ClauseStrategyUtils::initializeWildcardBothArg(argumentList, false, di);
}

bool FollowsStrategy::isClauseHold(const std::string& firstItem, const std::string& secondItem) {
    return (this->isTransitive)
        ? pkbInterface->isAssociatedT(stoi(firstItem), stoi(secondItem))
        : pkbInterface->isAssociated(stoi(firstItem), stoi(secondItem));
}

bool FollowsStrategy::isClauseHold() {
    return pkbInterface->hasAssociated();
}

bool FollowsStrategy::isClauseHoldKey(const std::string& key) {
    return pkbInterface->hasAssociatedByKey(stoi(key));
}

bool FollowsStrategy::isClauseHoldValue(const std::string& value) {
    return pkbInterface->hasAssociatedByValue(stoi(value));
}

bool FollowsStrategy::initializeItemMap(EntityArgument* arg1, EntityArgument* arg2) {
    std::unordered_map<int, std::unordered_set<int>> result;
    if (this->isTransitive) {
        result = pkbInterface->getTEntries();
    } else {
        std::unordered_map<int, int> followEntries = pkbInterface->getFollowsEntries();
        result = CollectionUtils::mapToMapSet(followEntries);
    }

    itemMap = ConversionUtils::convertIntToStringMapSet(result);

    bool isBothStmt = StmtStmtEntity::checkType(arg1) && StmtStmtEntity::checkType(arg2);

    return isBothStmt;
}

bool FollowsStrategy::initializeItemMap(EntityArgument* arg1, InputArgument* arg2) {
    std::unordered_set<std::string> keyResult;

    if (this->isTransitive) {
        keyResult = ConversionUtils::convertIntToStringSet
        (pkbInterface->getTStmtsByValue(stoi(arg2->getValue())));
    } else {
        int result = pkbInterface->getStmtBefore(stoi(arg2->getValue()));
        if (result != -1) {
            keyResult.insert(std::to_string(result));
        }
    }

    std::unordered_set<std::string> valueSet = {arg2->getValue()};

    handleFilterAddCrossProductItemMap(keyResult, valueSet, arg1, nullptr);
    return true;
}

bool FollowsStrategy::initializeItemMap(InputArgument* arg1, EntityArgument* arg2) {
    std::unordered_set<std::string> valueResult;

    if (this->isTransitive) {
        valueResult = ConversionUtils::convertIntToStringSet(
            pkbInterface->getTStmtsByKey(stoi(arg1->getValue())));
    } else {
        int result = pkbInterface->getStmtAfter(stoi(arg1->getValue()));
        if (result != -1) {
            valueResult.insert(std::to_string(result));
        }
    }

    std::unordered_set<std::string> keySet = {arg1->getValue()};

    handleFilterAddCrossProductItemMap(keySet, valueResult, nullptr, arg2);
    return true;
}

void FollowsStrategy::setPKBInterface(DI& di) {
    setPKBInterface(&di.getService<IFollowsGetter>());
}

void FollowsStrategy::setPKBInterface(IFollowsGetter* pkbInterface) {
    this->pkbInterface = pkbInterface;
}

FollowsStrategy::FollowsStrategy() : FollowsStrategy(false) {}
FollowsStrategy::FollowsStrategy(bool isTransitive) : FollowsStrategy(nullptr, isTransitive) {}
FollowsStrategy::FollowsStrategy(IFollowsGetter* pkbInterface) :
    FollowsStrategy(pkbInterface, false) {}

FollowsStrategy::FollowsStrategy(IFollowsGetter* pkbInterface, bool isTransitive) :
    ClauseStrategy() {
    setPKBInterface(pkbInterface);
    this->isTransitive = isTransitive;
}
