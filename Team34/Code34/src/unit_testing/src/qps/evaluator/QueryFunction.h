#pragma once

#include <memory>
#include <unordered_set>
#include <unordered_map>

#include "common/ConversionUtils.h"
#include "common/exceptions/ErrorStatus.h"
#include "qps/argument/entity/EntityArgument.h"
#include "qps/argument/entity/VariableEntity.h"
#include "qps/clause/Clause.h"
#include "qps/evaluator/Evaluator.h"
#include "qps/query/AbstractQuery.h"

namespace query_func {
    static void TEST_SINGLESELECT_QUERY(std::shared_ptr<EntityArgument>& selection,
        std::vector<std::shared_ptr<Clause>>& clauseList,
        ErrorStatus errorStatus,
        std::unordered_set<std::string>& expectedResult) {
        AbstractQuery query;
        query.updateStatus(errorStatus);
        query.addSelection(selection);

        for (auto& eachClause : clauseList) {
            query.addClause(eachClause);
        }

        Evaluator evaluator;
        evaluator.processQuery(query);

        std::unordered_set<std::string> result = query.getResult()->getSynonymValues(selection->getValue());

        REQUIRE(result == expectedResult);
    }
}
