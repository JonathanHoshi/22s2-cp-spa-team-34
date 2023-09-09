// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once

#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

#include "qps/clause/ClauseResult.h"
#include "qps/clause/strategy/ClauseStrategy.h"
#include "qps/query/QueryResult.h"

class Clause {
private:
    std::vector<std::shared_ptr<Argument>> argumentList;
    std::shared_ptr<ClauseStrategy> strategy;

    void addArgument(std::shared_ptr<Argument> newArg);

public:
    Clause(std::shared_ptr<ClauseStrategy> strategy, std::shared_ptr<Argument> firstArgument,
        std::shared_ptr<Argument> secondArgument);
    Clause(std::shared_ptr<ClauseStrategy> strategy, std::shared_ptr<Argument> firstArgument,
        std::shared_ptr<Argument> secondArgument, std::shared_ptr<Argument> thirdArgument);

    void initializeClause(DI& di);
    ClauseResult process(QueryResult& resultTable);

    std::vector<std::shared_ptr<Argument>> getArgumentList();
    std::unordered_set<std::string> getSynonymList();

    class ClauseComparator {
    private:
        std::unordered_set<std::string>* processedSynonym;

    public:
        explicit ClauseComparator(std::unordered_set<std::string>& processedSynonym) {
            this->processedSynonym = &processedSynonym;
        }

        bool operator()(std::shared_ptr<Clause>& o1, std::shared_ptr<Clause>& o2) {
            int o1Syn = o1->getSynonymList().size();
            int o2Syn = o2->getSynonymList().size();
            for (auto& syn : o1->getSynonymList()) {
                if (processedSynonym->count(syn) > 0) {
                    o1Syn--;
                }
            }
            for (auto& syn : o2->getSynonymList()) {
                if (processedSynonym->count(syn) > 0) {
                    o2Syn--;
                }
            }
            if (o1Syn == o2Syn) {
                return o1->strategy > o2->strategy;
            } else {
                return o1Syn < o2Syn;
            }
        }
    };
};
