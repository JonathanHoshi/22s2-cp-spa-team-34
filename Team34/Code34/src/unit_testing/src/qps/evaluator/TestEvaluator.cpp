#include <memory>
#include <unordered_map>
#include <unordered_set>

#include "catch.hpp"
#include "common/ConversionUtils.h"
#include "common/exceptions/ErrorStatus.h"
#include "qps/argument/entity/EntityArgument.h"
#include "qps/argument/entity/VariableEntity.h"
#include "qps/clause/Clause.h"
#include "qps/evaluator/Evaluator.h"
#include "qps/query/AbstractQuery.h"
#include "QueryFunction.h"

using namespace query_func;

// stmt s, s1; assign a, a1; while w; if ifs; variable v, v1; 
// procedure p, p1; constant c; read re; print pn; call cl;

TEST_CASE("Evaluate Syntax Error") {
    std::shared_ptr<EntityArgument> selection = std::make_shared<VariableEntity>("v", "");
    std::unordered_set<std::string> expectedResult;
    std::vector<std::shared_ptr<Clause>> clauseList;

    TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::SYNTAX, expectedResult);
}

TEST_CASE("Evaluate Semantic Error") {
    std::shared_ptr<EntityArgument> selection = std::make_shared<VariableEntity>("v", "");
    std::unordered_set<std::string> expectedResult;
    std::vector<std::shared_ptr<Clause>> clauseList;

    TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::SEMANTIC, expectedResult);
}
