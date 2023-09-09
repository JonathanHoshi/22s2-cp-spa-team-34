// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "ClauseStrategy.h"
#include "common/CollectionUtils.h"

bool ClauseStrategy::isAnyWildCard(std::shared_ptr<Argument>& first,
    std::shared_ptr<Argument>& second) {
    return WildcardEntity::checkInstance(first.get())
        || WildcardEntity::checkInstance(second.get());
}

bool ClauseStrategy::isSynonym(Argument* arg) {
    return EntityArgument::checkInstance(arg)
        && !WildcardEntity::checkInstance(arg);
}

bool ClauseStrategy::isBothNewSynonym(QueryResult& resultTable,
    EntityArgument* first, EntityArgument* second) {
    return isNewSynonym(resultTable, first) && isNewSynonym(resultTable, second);
}

bool ClauseStrategy::isBothOldSynonym(QueryResult& resultTable,
    EntityArgument* first, EntityArgument* second) {
    return !isNewSynonym(resultTable, first)
        && !isNewSynonym(resultTable, second);
}

bool ClauseStrategy::isNewSynonym(QueryResult& resultTable, EntityArgument* arg) {
    return !resultTable.hasSynonym(arg->getValue());
}

void ClauseStrategy::initializeArgument(EntityArgument* arg1, EntityArgument* arg2) {}

void ClauseStrategy::processBothSynonym(QueryResult& resultTable,
    EntityArgument* first, EntityArgument* second) {
    if (!isBothNewSynonym(resultTable, first, second)
        && !isBothOldSynonym(resultTable, first, second)) {
        std::unordered_set<std::string> resultSet;
        initializeArgument(first, second);
        if (isNewSynonym(resultTable, first)) {
            resultSet = resultTable.getSynonymValues(second->getValue());
            initializeCrossProductItemMap(first, resultSet);
        } else {
            resultSet = resultTable.getSynonymValues(first->getValue());
            initializeCrossProductItemMap(resultSet, second);
        }
        return;
    } else if (isBothNewSynonym(resultTable, first, second)) {
        bool filteredStatus = initializeItemMap(first, second);
        isFiltered = (isSameSynonym) ? false : filteredStatus;
        return;
    }

    initializeArgument(first, second);
    for (auto& [key, valueSet] : resultTable.getSynonymPair(first->getValue(),
        second->getValue())) {
        for (std::string value : valueSet) {
            CollectionUtils::insert(this->itemMap, key, value);
        }
    }
}

void ClauseStrategy::processLeftSynonym(QueryResult& resultTable,
    EntityArgument* first, InputArgument* second) {
    if (isNewSynonym(resultTable, first)) {
        isFiltered = initializeItemMap(first, second);
        return;
    }

    initializeArgument(first, nullptr);
    for (std::string key : resultTable.getSynonymValues(first->getValue())) {
        CollectionUtils::insert(itemMap, key, second->getValue());
    }
}

void ClauseStrategy::processRightSynonym(QueryResult& resultTable,
    InputArgument* first, EntityArgument* second) {
    if (isNewSynonym(resultTable, second)) {
        isFiltered = initializeItemMap(first, second);
        return;
    }

    initializeArgument(nullptr, second);
    for (std::string value : resultTable.getSynonymValues(second->getValue())) {
        CollectionUtils::insert(itemMap, first->getValue(), value);
    }
}

void ClauseStrategy::processWildcard(QueryResult& resultTable,
    Argument* first, Argument* second) {
    bool isFirstWildcard = WildcardEntity::checkInstance(first);
    bool isSecondWildcard = WildcardEntity::checkInstance(second);

    if (isFirstWildcard && isSecondWildcard) {
        isFiltered = true;
        if (isClauseHold()) {
            clauseResult.setClausePass();
        }
        return;
    }

    if (isFirstWildcard && !isSecondWildcard) {
        processLeftWildcard(resultTable, WildcardEntity::cast(first), second);
    } else if (!isFirstWildcard && isSecondWildcard) {
        processRightWildcard(resultTable, first, WildcardEntity::cast(second));
    }
}

void ClauseStrategy::processLeftWildcard(QueryResult& resultTable,
    WildcardEntity* first, Argument* second) {
    if (!isSynonym(second)) {
        isFiltered = true;
        if (isClauseHoldValue(second->getValue())) {
            clauseResult.setClausePass();
        }
        return;
    }

    EntityArgument* secondEntity = EntityArgument::cast(second);
    clauseResult.initializeSynonym(second->getValue());

    if (!isNewSynonym(resultTable, secondEntity)) {
        std::unordered_set<std::string> resultSet =
            resultTable.getSynonymValues(secondEntity->getValue());
        initializeCrossProductItemMap(first, resultSet);
    } else {
        initializeItemMap(first, secondEntity);
    }
}

void ClauseStrategy::processRightWildcard(QueryResult& resultTable,
    Argument* first, WildcardEntity* second) {
    if (!isSynonym(first)) {
        isFiltered = true;
        if (isClauseHoldKey(first->getValue())) {
            clauseResult.setClausePass();
        }
        return;
    }

    EntityArgument* firstEntity = EntityArgument::cast(first);
    clauseResult.initializeSynonym(first->getValue());

    if (!isNewSynonym(resultTable, firstEntity)) {
        std::unordered_set<std::string> resultSet =
            resultTable.getSynonymValues(firstEntity->getValue());
        initializeCrossProductItemMap(resultSet, second);
    } else {
        initializeItemMap(firstEntity, second);  // populate ItemMap like normal
    }
}

ClauseStrategy::ClauseStrategy() {
    isSameSynonym = false;
    isFiltered = false;
}

void ClauseStrategy::
handleCrossProductAddItemMap(std::unordered_set<std::string>& firstItems,
    std::unordered_set<std::string>& secondItems) {
    for (std::string first : firstItems) {
        for (std::string second : secondItems) {
            CollectionUtils::insert(itemMap, first, second);
        }
    }
}

void ClauseStrategy::
handleFilterAddCrossProductItemMap(std::unordered_set<std::string>& firstItems,
    std::unordered_set<std::string>& secondItems,
    EntityArgument* arg1, EntityArgument* arg2) {
    if (arg1 != nullptr) {
        filterItem(firstItems, arg1);
    }

    if (arg2 != nullptr) {
        filterItem(secondItems, arg2);
    }

    handleCrossProductAddItemMap(firstItems, secondItems);
}

void ClauseStrategy::filterItem(std::unordered_set<std::string>& itemResult,
    EntityArgument* arg) {
    std::unordered_set<std::string> filteredSet;
    std::unordered_set<std::string> validItems = arg->getPKBValueList();

    for (std::string item : itemResult) {
        std::string value = arg->getAttrFromPKB(item);

        if (validItems.find(item) != validItems.end() ||
            validItems.find(value) != validItems.end()) {
            filteredSet.emplace(item);
        }
    }

    itemResult = filteredSet;
}

void ClauseStrategy::processItemMap(std::vector<std::shared_ptr<Argument>>& argumentList) {
    std::shared_ptr<Argument> firstArg = argumentList[0];
    std::shared_ptr<Argument> secondArg = argumentList[1];

    bool isFirstSpecial = InputArgument::checkInstance(firstArg.get())
        || WildcardEntity::checkInstance(firstArg.get());
    bool isSecondSpecial = InputArgument::checkInstance(secondArg.get())
        || WildcardEntity::checkInstance(secondArg.get());

    std::unordered_set<std::string> firstItemValues;

    if (isFiltered && !isFirstSpecial && !isSecondSpecial) {
        if (!itemMap.empty()) {
            clauseResult.setClausePass();
            clauseResult.addMap(itemMap);
        }
        return;
    }

    // Filter keys of to ensure correct entity items
    if (!isFirstSpecial) {
        firstItemValues = EntityArgument::cast(firstArg.get())->getPKBValueList();
    }

    for (auto& [key, valueSet] : itemMap) {
        if (!isFiltered && !isFirstSpecial && firstItemValues.find(key) == firstItemValues.end()) {
            continue;
        }

        if (!isFiltered && !isSecondSpecial) {
            filterItem(valueSet, EntityArgument::cast(secondArg.get()));
        }

        handleItemPair(key, valueSet, isFirstSpecial, isSecondSpecial);
    }
}

void ClauseStrategy::handleItemPair(const std::string& firstItem,
    const std::unordered_set<std::string>& secondItemSet,
    bool isFirstSpecial, bool isSecondSpecial) {
    for (std::string secondItem : secondItemSet) {
        if (!isFirstSpecial && !isSecondSpecial && isSameSynonym && firstItem != secondItem
            || !isFiltered && !isClauseHold(firstItem, secondItem)) {
            continue;
        }

        clauseResult.setClausePass();

        if (!isFirstSpecial && isSecondSpecial) {
            clauseResult.addEntry(firstItem);
            return;
        } else if (isFirstSpecial && !isSecondSpecial) {
            clauseResult.addEntry(secondItem);
        } else if (!isFirstSpecial && !isSecondSpecial && !isSameSynonym) {
            clauseResult.addEntry(firstItem, secondItem);
        } else if (!isFirstSpecial && !isSecondSpecial && isSameSynonym) {
            clauseResult.addEntry(firstItem);
        }
    }
}

void ClauseStrategy::handleAddingDoubleItem(std::string firstItem, std::string secondItem) {
    if (isClauseHold(firstItem, secondItem)) {
        clauseResult.setClausePass();
        clauseResult.addEntry(firstItem, secondItem);
    }
}

void ClauseStrategy::handleInitializeBothSynonym(Argument* arg1, Argument* arg2) {
    isSameSynonym = (*arg1 == *arg2);
    if (isSameSynonym) {
        clauseResult.initializeSynonym(arg1->getValue());
    } else {
        clauseResult.initializeSynonym(arg1->getValue(), arg2->getValue());
    }
}

void ClauseStrategy::initializeCrossProductItemMap(EntityArgument* arg1,
    std::unordered_set<std::string>& arg2Results) {
    std::unordered_set<std::string> arg1Results = arg1->getPKBValueList();

    handleCrossProductAddItemMap(arg1Results, arg2Results);
}

void ClauseStrategy::initializeCrossProductItemMap(std::unordered_set<std::string>& arg1Results,
    EntityArgument* arg2) {
    std::unordered_set<std::string> arg2Results = arg2->getPKBValueList();
    handleCrossProductAddItemMap(arg1Results, arg2Results);
}

void ClauseStrategy::initializeStrategy(DI& di,
    std::vector<std::shared_ptr<Argument>>& argumentList) {
    itemMap.clear();
    clauseResult.clear();
    initializeWildcard(argumentList, di);
    for (const auto& arg : argumentList) {
        if (EntityArgument::checkInstance(arg.get())
            && !WildcardEntity::checkInstance(arg.get())) {
            EntityArgument::cast(arg.get())->setPKBInterface(di);
        }
    }
    setPKBInterface(di);
}

void ClauseStrategy::initialize(QueryResult& resultTable,
    std::vector<std::shared_ptr<Argument>>& argumentList) {
    std::shared_ptr<Argument> arg1 = argumentList[0];
    std::shared_ptr<Argument> arg2 = argumentList[1];

    if (isAnyWildCard(arg1, arg2)) {
        processWildcard(resultTable, arg1.get(), arg2.get());
    } else if (isSynonym(arg1.get()) && isSynonym(arg2.get())) {
        handleInitializeBothSynonym(arg1.get(), arg2.get());
        processBothSynonym(resultTable, EntityArgument::cast(arg1.get()),
            EntityArgument::cast(arg2.get()));
    } else if (isSynonym(arg1.get()) && !isSynonym(arg2.get())) {
        clauseResult.initializeSynonym(arg1->getValue());
        processLeftSynonym(resultTable, EntityArgument::cast(arg1.get()),
            InputArgument::cast(arg2.get()));
    } else if (!isSynonym(arg1.get()) && isSynonym(arg2.get())) {
        clauseResult.initializeSynonym(arg2->getValue());
        processRightSynonym(resultTable, InputArgument::cast(arg1.get()),
            EntityArgument::cast(arg2.get()));
    } else {
        CollectionUtils::insert(itemMap, arg1->getValue(), arg2->getValue());
        isFiltered = false;
    }
}

ClauseResult ClauseStrategy::execute(QueryResult& resultTable,
    std::vector<std::shared_ptr<Argument>>& argumentList) {
    initialize(resultTable, argumentList);
    processItemMap(argumentList);
    return clauseResult;
}

int ClauseStrategy::getPreferenceValue() {
    return DEFAULT_PREFERENCE_VALUE;
}

bool ClauseStrategy::operator<(ClauseStrategy& other) {
    return getPreferenceValue() < other.getPreferenceValue();
}
