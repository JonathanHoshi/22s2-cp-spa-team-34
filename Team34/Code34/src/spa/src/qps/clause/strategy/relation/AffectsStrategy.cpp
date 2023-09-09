// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.
#include <unordered_map>
#include <unordered_set>
#include "AffectsStrategy.h"
#include "common/ConversionUtils.h"
#include "qps/argument/entity/stmt/AssignStmtEntity.h"
#include "qps/argument/entity/stmt/StmtStmtEntity.h"

void AffectsStrategy::initializeWildcard(std::vector<std::shared_ptr<Argument>>& argumentList,
    DI& di) {
    ClauseStrategyUtils::initializeWildcardBothArg(argumentList, false, di);
}

bool AffectsStrategy::isClauseHold(const std::string& firstItem,
    const std::string& secondItem) {
    return (this->isTransitive)
        ? pkbInterface->isAffectsT(stoi(firstItem), stoi(secondItem))
        : pkbInterface->isAffects(stoi(firstItem), stoi(secondItem));
}

bool AffectsStrategy::isClauseHold() {
    return pkbInterface->hasAffects();
}

bool AffectsStrategy::isClauseHoldKey(const std::string& key) {
    return pkbInterface->hasAffectsByKeyStmt(stoi(key));
}

bool AffectsStrategy::isClauseHoldValue(const std::string& value) {
    return pkbInterface->hasAffectsByAffectedStmt(stoi(value));
}

bool AffectsStrategy::initializeItemMap(EntityArgument* arg1, EntityArgument* arg2) {
    if (!checkValidSynType(arg1) || !checkValidSynType(arg2)) {
        itemMap = std::unordered_map<std::string, std::unordered_set<std::string>>();
        return false;
    }

    itemMap = (this->isTransitive)
        ? ConversionUtils::convertIntToStringMapSet(pkbInterface->getAffectsTEntries())
        : ConversionUtils::convertIntToStringMapSet(pkbInterface->getAffectsEntries());
    return true;
}

bool AffectsStrategy::initializeItemMap(EntityArgument* arg1, InputArgument* arg2) {
    if (!checkValidSynType(arg1)) {
        return false;
    }
    std::unordered_set<std::string> keyResult = (this->isTransitive)
        ? ConversionUtils::
        convertIntToStringSet(pkbInterface->getTKeyStmtsByAffectedStmt(stoi(arg2->getValue())))
        : ConversionUtils::
        convertIntToStringSet(pkbInterface->getKeyStmtsByAffectedStmt(stoi(arg2->getValue())));

    std::unordered_set<std::string> valueSet = {arg2->getValue()};

    handleFilterAddCrossProductItemMap(keyResult, valueSet, arg1, nullptr);
    return true;
}

bool AffectsStrategy::initializeItemMap(InputArgument* arg1, EntityArgument* arg2) {
    if (!checkValidSynType(arg2)) {
        return false;
    }
    std::unordered_set<std::string> valueResult = (this->isTransitive)
        ? ConversionUtils::
        convertIntToStringSet(pkbInterface->getTAffectedStmtsByKeyStmt(stoi(arg1->getValue())))
        : ConversionUtils::
        convertIntToStringSet(pkbInterface->getAffectedStmtsByKeyStmt(stoi(arg1->getValue())));

    std::unordered_set<std::string> keySet = {arg2->getValue()};

    handleFilterAddCrossProductItemMap(keySet, valueResult, nullptr, arg2);

    return true;
}

void AffectsStrategy::setPKBInterface(DI& di) {
    setPKBInterface(&di.getService<IAffectsGetter>());
}

void AffectsStrategy::setPKBInterface(IAffectsGetter* pkbInterface) {
    this->pkbInterface = pkbInterface;
}

bool AffectsStrategy::checkValidSynType(EntityArgument* arg) {
    return StmtStmtEntity::checkType(arg) || AssignStmtEntity::checkType(arg)
        || WildcardEntity::checkInstance(arg);
}

AffectsStrategy::AffectsStrategy() : AffectsStrategy(false) {}
AffectsStrategy::AffectsStrategy(bool isTransitive) :
    AffectsStrategy(nullptr, isTransitive) {}
AffectsStrategy::AffectsStrategy(IAffectsGetter* pkbInterface) :
    AffectsStrategy(pkbInterface, false) {}

AffectsStrategy::AffectsStrategy(IAffectsGetter* pkbInterface, bool isTransitive) :
    ClauseStrategy() {
    setPKBInterface(pkbInterface);
    this->isTransitive = isTransitive;
}

int AffectsStrategy::getPreferenceValue() {
    return AFFECTS_PREFERENCE_VALUE;
}
