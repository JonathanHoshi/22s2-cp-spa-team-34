// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.
#pragma once

#include <memory>
#include <vector>
#include <string>
#include "pkb/interfaces/INextGetter.h"
#include "qps/argument/Argument.h"
#include "qps/clause/Clause.h"
#include "qps/clause/strategy/ClauseStrategy.h"

class NextStrategy : public ClauseStrategy {
protected:
    static const int NEXT_PREFERENCE_VALUE = 2;

    INextGetter* pkbInterface;
    bool isTransitive;

    void initializeWildcard(std::vector<std::shared_ptr<Argument>>& argumentList,
        DI& di) override;

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
    void setPKBInterface(INextGetter* pkbInterface);

    int getPreferenceValue() override;

public:
    NextStrategy();
    explicit NextStrategy(bool isTransitive);
    explicit NextStrategy(INextGetter* pkbInterface);
    NextStrategy(INextGetter* pkbInterface, bool isTransitive);
};
