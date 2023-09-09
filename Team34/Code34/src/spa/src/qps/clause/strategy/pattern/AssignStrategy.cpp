// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.
#include <unordered_map>
#include <unordered_set>
#include "AssignStrategy.h"
#include "common/CollectionUtils.h"
#include "common/ConversionUtils.h"

void AssignStrategy::initializeWildcard(std::vector<std::shared_ptr<Argument>>& argumentList,
    DI& di) {
    ClauseStrategyUtils::initializeWildcardRightArgVar(argumentList[1], di);
}

bool AssignStrategy::isClauseHold(const std::string& firstItem,
    const std::string& secondItem) {
    return (this->expression != nullptr)
        ? (this->isPartial)
        ? pkbInterface->isValidPartialPattern(stoi(firstItem), secondItem, expression)
        : pkbInterface->isValidFullPattern(stoi(firstItem), secondItem, expression)
        : pkbInterface->isValidPattern(stoi(firstItem), secondItem);
}

bool AssignStrategy::isClauseHold() {
    return (this->expression != nullptr)
        ? (this->isPartial)
        ? pkbInterface->hasValidPartialPattern(expression)
        : pkbInterface->hasValidFullPattern(expression)
        : pkbInterface->hasValidPattern();
}

bool AssignStrategy::isClauseHoldKey(const std::string& key) {
    return (this->expression != nullptr)
        ? (this->isPartial)
        ? pkbInterface->hasValidPartialPattern(stoi(key), expression)
        : pkbInterface->hasValidFullPattern(stoi(key), expression)
        : pkbInterface->hasValidPattern(stoi(key));
}

bool AssignStrategy::isClauseHoldValue(const std::string& value) {
    return (this->expression != nullptr)
        ? (this->isPartial)
        ? pkbInterface->hasValidPartialPattern(value, expression)
        : pkbInterface->hasValidFullPattern(value, expression)
        : pkbInterface->hasValidPattern(value);
}

bool AssignStrategy::initializeItemMap(EntityArgument* arg1, EntityArgument* arg2) {
    std::unordered_map<int, std::string> mapResult = (this->expression != nullptr)
        ? (this->isPartial)
        ? pkbInterface->getStmtsVarByValidPartialPattern(expression)
        : pkbInterface->getStmtsVarByValidFullPattern(expression)
        : pkbInterface->getStmtsVar();
    std::unordered_map<int, std::unordered_set<std::string>> strMapResult =
        CollectionUtils::mapToMapSet(mapResult);
    itemMap = ConversionUtils::convertIntToStringMapSet(strMapResult);
    return true;
}

bool AssignStrategy::initializeItemMap(EntityArgument* arg1, InputArgument* arg2) {
    std::unordered_set<int> keyResult = (this->expression != nullptr)
        ? (this->isPartial)
        ? pkbInterface->getStmtsByVarValidPartialPattern(arg2->getValue(), expression)
        : pkbInterface->getStmtsByVarValidFullPattern(arg2->getValue(), expression)
        : pkbInterface->getStmtsByVar(arg2->getValue());

    std::unordered_set<std::string> valueSet = {arg2->getValue()};

    std::unordered_set<std::string> keyStringResult =
        ConversionUtils::convertIntToStringSet(keyResult);
    handleCrossProductAddItemMap(keyStringResult, valueSet);
    return true;
}

bool AssignStrategy::initializeItemMap(InputArgument* arg1, EntityArgument* arg2) {
    std::string value = (this->expression != nullptr)
        ? (this->isPartial)
        ? pkbInterface->getVarByStmtValidPartialPattern(stoi(arg1->getValue()), expression)
        : pkbInterface->getVarByStmtValidFullPattern(stoi(arg1->getValue()), expression)
        : pkbInterface->getVarByStmt(stoi(arg1->getValue()));

    std::unordered_set<std::string> keySet = {arg1->getValue()};
    std::unordered_set<std::string> valueSet = {value};

    handleCrossProductAddItemMap(keySet, valueSet);
    return true;
}

void AssignStrategy::setPKBInterface(DI& di) {
    setPKBInterface(&di.getService<IAssignPatternGetter>());
}

void AssignStrategy::setPKBInterface(IAssignPatternGetter* pkbInterface) {
    this->pkbInterface = pkbInterface;
}

AssignStrategy::AssignStrategy() : AssignStrategy(false) {}
AssignStrategy::AssignStrategy(bool isPartial) : AssignStrategy(nullptr, isPartial) {}
AssignStrategy::AssignStrategy(IAssignPatternGetter* pkbInterface)
    : AssignStrategy(pkbInterface, false) {}

AssignStrategy::AssignStrategy(IAssignPatternGetter* pkbInterface, bool isPartial) :
    ClauseStrategy() {
    setPKBInterface(pkbInterface);
    this->isPartial = isPartial;
}

ClauseResult AssignStrategy::execute(QueryResult& result,
    std::vector<std::shared_ptr<Argument>>& argumentList) {
    // Check whether it is an expression input or wildcard input
    if (ExpressionInput::checkInstance(argumentList[2].get())) {
        ExpressionInput* exprInput = dynamic_cast<ExpressionInput*>(argumentList[2].get());
        this->expression = exprInput->getAst();
    } else {
        this->expression = nullptr;
    }
    return ClauseStrategy::execute(result, argumentList);
}
