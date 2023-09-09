// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once

#include <string>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "di/DI.h"
#include "qps/argument/Argument.h"
#include "qps/argument/entity/ProcedureEntity.h"
#include "qps/argument/entity/WildcardEntity.h"
#include "qps/argument/input/InputArgument.h"
#include "qps/clause/ClauseResult.h"
#include "qps/clause/strategy/ClauseStrategyUtils.h"
#include "qps/query/QueryResult.h"

class ClauseStrategy {
private:
    static const int DEFAULT_PREFERENCE_VALUE = 5;
    bool isFiltered;

    bool isAnyWildCard(std::shared_ptr<Argument>& first, std::shared_ptr<Argument>& second);
    bool isSynonym(Argument* arg);
    bool isBothNewSynonym(QueryResult& resultTable, EntityArgument* first, EntityArgument* second);
    bool isBothOldSynonym(QueryResult& resultTable, EntityArgument* first, EntityArgument* second);
    bool isNewSynonym(QueryResult& resultTable, EntityArgument* arg);

    void processBothSynonym(QueryResult& resultTable, EntityArgument* first,
        EntityArgument* second);
    void processLeftSynonym(QueryResult& resultTable, EntityArgument* first,
        InputArgument* second);
    void processRightSynonym(QueryResult& resultTable, InputArgument* first,
        EntityArgument* second);
    void processWildcard(QueryResult& resultTable, Argument* first, Argument* second);
    void processLeftWildcard(QueryResult& resultTable, WildcardEntity* first,
        Argument* second);
    void processRightWildcard(QueryResult& resultTable, Argument* first, WildcardEntity* second);

    void processItemMap(std::vector<std::shared_ptr<Argument>>& argumentList);
    void handleItemPair(const std::string& firstItem,
        const std::unordered_set<std::string>& secondItemSet, bool isFirstInput,
        bool isSecondInput);
    void handleAddingDoubleItem(std::string firstItem, std::string secondItem);
    void handleInitializeBothSynonym(Argument* arg1, Argument* arg2);

protected:
    ClauseResult clauseResult;
    std::unordered_map<std::string, std::unordered_set<std::string>> itemMap;
    bool isSameSynonym;

    ClauseStrategy();
    void handleCrossProductAddItemMap(std::unordered_set<std::string>& firstItems,
        std::unordered_set<std::string>& secondItems);
    void handleFilterAddCrossProductItemMap(std::unordered_set<std::string>& firstItems,
        std::unordered_set<std::string>& secondItems, EntityArgument* arg1, EntityArgument* arg2);
    void filterItem(std::unordered_set<std::string>& itemResult, EntityArgument* arg);

    virtual void initializeWildcard(std::vector<std::shared_ptr<Argument>>& argumentList,
        DI& di) = 0;
    virtual bool isClauseHold(const std::string& firstItem, const std::string& secondItem) = 0;
    virtual bool isClauseHold() = 0;
    virtual bool isClauseHoldKey(const std::string& key) = 0;
    virtual bool isClauseHoldValue(const std::string& value) = 0;

    // Each clause handles how it populate 1 synonym from PKB
    // and cross product with 1 old synonym values -> REQUIRE FILTERING
    virtual void initializeCrossProductItemMap(EntityArgument* arg1,
        std::unordered_set<std::string>& arg2Results);
    virtual void initializeCrossProductItemMap(std::unordered_set<std::string>& arg1Results,
        EntityArgument* arg2);

    // Each clause handles how it populate 2 synonym from PKB
    virtual bool initializeItemMap(EntityArgument* arg1, EntityArgument* arg2) = 0;

    // Each clause handles how it populate 1 synonym and 1 input from PKB
    virtual bool initializeItemMap(EntityArgument* arg1, InputArgument* arg2) = 0;
    virtual bool initializeItemMap(InputArgument* arg1, EntityArgument* arg2) = 0;
    virtual void initializeArgument(EntityArgument* arg1, EntityArgument* arg2);

    virtual void setPKBInterface(DI& di) = 0;

    virtual void initialize(QueryResult& resultTable,
        std::vector<std::shared_ptr<Argument>>& argumentList);

    virtual int getPreferenceValue();

public:
    virtual void initializeStrategy(DI& di, std::vector<std::shared_ptr<Argument>>& argumentList);
    virtual ClauseResult execute(QueryResult& resultTable,
        std::vector<std::shared_ptr<Argument>>& argumentList);
    bool operator<(ClauseStrategy& other);
};
