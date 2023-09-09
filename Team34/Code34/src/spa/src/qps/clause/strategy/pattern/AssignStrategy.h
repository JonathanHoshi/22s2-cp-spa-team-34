// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once

#include <string>
#include <vector>
#include <memory>
#include "pkb/interfaces/IAssignPatternGetter.h"
#include "qps/argument/input/ExpressionInput.h"
#include "qps/clause/strategy/ClauseStrategy.h"
#include "qps/query/QueryResult.h"



class AssignStrategy : public ClauseStrategy {
protected:
    IAssignPatternGetter* pkbInterface;
    bool isPartial;
    std::shared_ptr<ExpressionNode> expression;

    void initializeWildcard(std::vector<std::shared_ptr<Argument>>& argumentList, DI& di) override;

    bool isClauseHold(const std::string& firstItem, const std::string& secondItem) override;
    bool isClauseHold() override;
    bool isClauseHoldKey(const std::string& key) override;
    bool isClauseHoldValue(const std::string& value) override;

    // Each clause handles how it populate 2 synonym from PKB
    bool initializeItemMap(EntityArgument* arg1, EntityArgument* arg2) override;

    // Each clause handles how it populate 1 synonym and 1 input from PKB
    bool initializeItemMap(EntityArgument* arg1, InputArgument* arg2) override;
    bool initializeItemMap(InputArgument* arg1, EntityArgument* arg2) override;
    void setPKBInterface(DI& di) override;

    void setPKBInterface(IAssignPatternGetter* pkbInterface);

public:
    AssignStrategy();
    explicit AssignStrategy(bool isPartial);
    explicit AssignStrategy(IAssignPatternGetter* pkbInterface);
    AssignStrategy(IAssignPatternGetter* pkbInterface, bool isPartial);

    ClauseResult execute(QueryResult& result,
        std::vector<std::shared_ptr<Argument>>& argumentList) override;
};
