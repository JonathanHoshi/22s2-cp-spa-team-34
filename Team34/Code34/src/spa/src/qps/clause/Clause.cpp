// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "Clause.h"

Clause::Clause(std::shared_ptr<ClauseStrategy> strategy,
    std::shared_ptr<Argument> firstArgument, std::shared_ptr<Argument> secondArgument) {
    addArgument(firstArgument);
    addArgument(secondArgument);
    this->strategy = strategy;
}

Clause::Clause(std::shared_ptr<ClauseStrategy> strategy, std::shared_ptr<Argument> firstArgument,
    std::shared_ptr<Argument> secondArgument,
    std::shared_ptr<Argument> thirdArgument) : Clause(strategy, firstArgument, secondArgument) {
    addArgument(thirdArgument);
}

void Clause::addArgument(std::shared_ptr<Argument> newArg) {
    this->argumentList.push_back(newArg);
}

void Clause::initializeClause(DI& di) {
    this->strategy->initializeStrategy(di, this->argumentList);
}

ClauseResult Clause::process(QueryResult& resultTable) {
    return this->strategy->execute(resultTable, this->argumentList);
}

std::vector<std::shared_ptr<Argument>> Clause::getArgumentList() {
    return this->argumentList;
}

std::unordered_set<std::string> Clause::getSynonymList() {
    std::unordered_set<std::string> result;

    for (auto& arg : argumentList) {
        if (EntityArgument::checkInstance(arg.get()) &&
            !WildcardEntity::checkInstance(arg.get())) {
            result.emplace(arg->getValue());
        }
    }

    return result;
}

