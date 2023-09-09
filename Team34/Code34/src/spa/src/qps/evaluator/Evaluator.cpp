// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.
#include <string>
#include <unordered_set>
#include "Evaluator.h"


void Evaluator::handleQueryProcess(AbstractQuery& query) {
    std::vector<std::shared_ptr<EntityArgument>> selectList = query.getSelectionList();
    std::vector<std::shared_ptr<Clause>> clauseList = query.getClauseList();

    bool isQueryPassed = processor.processQuery(clauseList, diInterface);

    if (!isQueryPassed || query.getSelectBoolean()) {
        QueryResult emptyResult(isQueryPassed);
        query.setQueryResult(emptyResult);
        return;
    }

    QueryResult result = processor.processResult(selectList, diInterface);
    query.setQueryResult(result);
}

Evaluator::Evaluator() : Evaluator(nullptr) {}
Evaluator::Evaluator(DI* diInterface) {
    this->diInterface = diInterface;
}

void Evaluator::processQuery(AbstractQuery& query) {
    if (query.getQueryStatus() != ErrorStatus::OK) {
        return;
    }

    return handleQueryProcess(query);
}
