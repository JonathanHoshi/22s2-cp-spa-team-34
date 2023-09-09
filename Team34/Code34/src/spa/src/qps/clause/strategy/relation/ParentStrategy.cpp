// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.
#include <unordered_set>
#include "ParentStrategy.h"
#include "common/ConversionUtils.h"
#include "qps/argument/entity/stmt/StmtStmtEntity.h"

void ParentStrategy::initializeWildcard(std::vector<std::shared_ptr<Argument>>& argumentList,
    DI& di) {
    ClauseStrategyUtils::initializeWildcardBothArg(argumentList, false, di);
}

bool ParentStrategy::isClauseHold(const std::string& firstItem, const std::string& secondItem) {
    return (this->isTransitive)
        ? pkbInterface->isAssociatedT(stoi(firstItem), stoi(secondItem))
        : pkbInterface->isAssociated(stoi(firstItem), stoi(secondItem));
}

bool ParentStrategy::isClauseHold() {
    return pkbInterface->hasAssociated();
}

bool ParentStrategy::isClauseHoldKey(const std::string& key) {
    return pkbInterface->hasAssociatedByKey(stoi(key));
}

bool ParentStrategy::isClauseHoldValue(const std::string& value) {
    return pkbInterface->hasAssociatedByValue(stoi(value));
}

bool ParentStrategy::initializeItemMap(EntityArgument* arg1, EntityArgument* arg2) {
    itemMap = (this->isTransitive)
        ? ConversionUtils::convertIntToStringMapSet(pkbInterface->getTEntries())
        : ConversionUtils::convertIntToStringMapSet(pkbInterface->getParentEntries());

    bool isBothStmt = StmtStmtEntity::checkType(arg1) && StmtStmtEntity::checkType(arg2);

    return isBothStmt;
}

bool ParentStrategy::initializeItemMap(EntityArgument* arg1, InputArgument* arg2) {
    std::unordered_set<std::string> keyResult;

    if (this->isTransitive) {
        keyResult = ConversionUtils::
            convertIntToStringSet(pkbInterface->getTStmtsByValue(stoi(arg2->getValue())));
    } else {
        int result = pkbInterface->getParentOf(stoi(arg2->getValue()));
        if (result != -1) {
            keyResult.insert(std::to_string(result));
        }
    }
    std::unordered_set<std::string> valueSet = {arg2->getValue()};

    handleFilterAddCrossProductItemMap(keyResult, valueSet, arg1, nullptr);
    return true;
}

bool ParentStrategy::initializeItemMap(InputArgument* arg1, EntityArgument* arg2) {
    std::unordered_set<std::string> valueResult = (this->isTransitive)
        ? ConversionUtils::
        convertIntToStringSet(pkbInterface->getTStmtsByKey(stoi(arg1->getValue())))
        : ConversionUtils::
        convertIntToStringSet(pkbInterface->getChildrenOf(stoi(arg1->getValue())));

    std::unordered_set<std::string> keySet = {arg2->getValue()};

    handleFilterAddCrossProductItemMap(keySet, valueResult, nullptr, arg2);

    return true;
}

void ParentStrategy::setPKBInterface(DI& di) {
    setPKBInterface(&di.getService<IParentGetter>());
}

void ParentStrategy::setPKBInterface(IParentGetter* pkbInterface) {
    this->pkbInterface = pkbInterface;
}

ParentStrategy::ParentStrategy() : ParentStrategy(false) {}
ParentStrategy::ParentStrategy(bool isTransitive) : ParentStrategy(nullptr, isTransitive) {}
ParentStrategy::ParentStrategy(IParentGetter* pkbInterface) :
    ParentStrategy(pkbInterface, false) {}

ParentStrategy::ParentStrategy(IParentGetter* pkbInterface, bool isTransitive) :
    ClauseStrategy() {
    setPKBInterface(pkbInterface);
    this->isTransitive = isTransitive;
}
