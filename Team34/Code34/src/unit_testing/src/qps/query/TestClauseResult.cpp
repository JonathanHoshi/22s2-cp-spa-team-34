#include <memory>
#include <unordered_map>
#include <unordered_set>

#include "catch.hpp"
#include "qps/clause/ClauseResult.h"

using namespace std;

// stmt s, s1; assign a, a1; while w; if ifs; variable v, v1; 
// procedure p, p1; constant c; read re; print pn; call cl;

TEST_CASE("Add single synonym entries") {
	ClauseResult result;

	result.initializeSynonym("a");
	result.addEntry("1");
	result.addEntry("2");
	result.addEntry("4");
	result.addEntry("8");

	vector<string> synonymSet = result.getClauseSynonyms();
	vector<string> expectedSynResult = { "a" };
	REQUIRE(synonymSet == expectedSynResult);

	unordered_map<string, unordered_set<string>> resultEntries = result.getResultMap();
	unordered_map<string, unordered_set<string>> expectedResult = { { "1", { } },
																	{ "2", { } },
																	{ "4", { } }, 
																	{ "8", { } } };

	REQUIRE(resultEntries == expectedResult);
}

TEST_CASE("Add double synonym entries") {
	ClauseResult result;

	result.initializeSynonym("a", "s");
	result.addEntry("1", "2");
	result.addEntry("1", "3");
	result.addEntry("2", "4");
	result.addEntry("4", "8");
	result.addEntry("4", "10");
	result.addEntry("4", "12");
	result.addEntry("8", "16");

	vector<string> synonymSet = result.getClauseSynonyms();
	vector<string> expectedSynResult = { "a", "s" };
	REQUIRE(synonymSet == expectedSynResult);

	unordered_map<string, unordered_set<string>> resultEntries = result.getResultMap();
	unordered_map<string, unordered_set<string>> expectedResult = { { "1", { "2", "3" } },
																	{ "2", { "4" } },
																	{ "4", { "8", "10", "12" } },
																	{ "8", { "16" } } };

	REQUIRE(resultEntries == expectedResult);
}
