#pragma once

#include <memory>
#include <unordered_set>
#include <unordered_map>

#include "catch.hpp"
#include "qps/QPS.h"

namespace query_func
{
    static void TEST_SINGLESELECT_QUERY(DI& di, std::string query, std::unordered_set<std::string>& expectedResult) {
        QPS qps;
        std::list<std::string> results = qps.process(query, di);
 
        std::list<std::string> expectedResultsList(expectedResult.begin(), expectedResult.end());
        expectedResultsList.sort();
        REQUIRE(results == expectedResultsList);
    }
}
