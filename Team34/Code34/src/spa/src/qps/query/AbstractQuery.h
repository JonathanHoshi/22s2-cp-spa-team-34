// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once

#include <memory>
#include <string>
#include <vector>

#include "qps/argument/Argument.h"
#include "qps/clause/Clause.h"
#include "qps/query/QueryResult.h"
#include "common/exceptions/ErrorStatus.h"

class AbstractQuery {
private:
    std::vector<std::shared_ptr<EntityArgument>> selectionList;
    bool isSelectBoolean;
    ErrorStatus queryStatus;
    std::vector<std::shared_ptr<Clause>> clauseList;
    QueryResult queryResult;

public:
    AbstractQuery();
    void addClause(std::shared_ptr<Clause> newClause);
    void addSelection(std::shared_ptr<EntityArgument> newSelection);
    // need to remove (check wif ryan's element)
    void addSelection(std::shared_ptr<Argument> newSelection);
    void updateStatus(ErrorStatus newStatus);
    void setSelectBoolean(bool isSelectBoolean);
    void setQueryResult(QueryResult& otherResult);
    bool getSelectBoolean();
    bool isSelectionEmpty();
    bool isClauseEmpty();

    std::vector<std::shared_ptr<EntityArgument>> getSelectionList();
    std::vector<std::shared_ptr<Clause>> getClauseList();
    ErrorStatus getQueryStatus();
    QueryResult* getResult();
};
