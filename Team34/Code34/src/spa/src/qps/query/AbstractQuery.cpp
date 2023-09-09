// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "AbstractQuery.h"

AbstractQuery::AbstractQuery() {
    queryStatus = ErrorStatus::OK;
    isSelectBoolean = false;
}

bool AbstractQuery::getSelectBoolean() {
    return this->isSelectBoolean;
}

void AbstractQuery::setSelectBoolean(bool isSelectBoolean) {
    this->isSelectBoolean = isSelectBoolean;
}

void AbstractQuery::setQueryResult(QueryResult& otherResult) {
    this->queryResult = otherResult;
}

void AbstractQuery::addClause(std::shared_ptr<Clause> newClause) {
    this->clauseList.push_back(newClause);
}

void AbstractQuery::addSelection(std::shared_ptr<EntityArgument> newSelection) {
    this->selectionList.push_back(newSelection);
}

void AbstractQuery::addSelection(std::shared_ptr<Argument> newSelection) {
    std::shared_ptr<EntityArgument> castSelection =
        std::dynamic_pointer_cast<EntityArgument>(newSelection);

    this->selectionList.push_back(castSelection);
}

void AbstractQuery::updateStatus(ErrorStatus newStatus) {
    this->queryStatus = newStatus;
}

bool AbstractQuery::isSelectionEmpty() {
    return selectionList.empty();
}

bool AbstractQuery::isClauseEmpty() {
    return clauseList.empty();
}

std::vector<std::shared_ptr<EntityArgument>> AbstractQuery::getSelectionList() {
    return this->selectionList;
}


std::vector<std::shared_ptr<Clause>> AbstractQuery::getClauseList() {
    return this->clauseList;
}

ErrorStatus AbstractQuery::getQueryStatus() {
    return this->queryStatus;
}

QueryResult* AbstractQuery::getResult() {
    return &this->queryResult;
}
