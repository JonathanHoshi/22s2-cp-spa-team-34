#include <memory>
#include <unordered_map>
#include <unordered_set>

#include "catch.hpp"
#include "qps/query/QueryResult.h"
#include "qps/clause/ClauseResult.h"
#include "common/CollectionUtils.h"

using namespace std;

// stmt s, s1; assign a, a1; while w; if ifs; variable v, v1; 
// procedure p, p1; constant c; read re; print pn; call cl;

bool vectorFind(vector<string>& vec, string entry) {
	for (string val : vec) {
		if (entry == val) {
			return true;
		}
	}
	return false;
}

bool checkResult(unordered_map<string, vector<string>>& resultEntries, unordered_map<string, vector<string>>& expectedResult) {
	int vectorSize = expectedResult.begin()->second.size();

	if (vectorSize != resultEntries.begin()->second.size()) {
		return false;
	}

	unordered_set<string> synonymSet;
	CollectionUtils::collapseKey(expectedResult, synonymSet);

	for (int i = 0; i < vectorSize; i++) {
		for (string syn : synonymSet) {
			if (!vectorFind(resultEntries[syn], expectedResult[syn][i])) {
				return false;
			}
		}
	}

	return true;
}

TEST_CASE("Add single synonym group entries") {
	QueryResult result;

	string synonym = "a";
	unordered_set<string> entrySet = { "1", "2", "3", "4" };

	result.addSynonymGroup(synonym, entrySet);

	unordered_map<string, vector<string>> resultEntries = result.getResultMap();
	unordered_map<string, vector<string>> expectedResult = { { "a", { "1", "2", "3", "4" } } };

	REQUIRE(checkResult(resultEntries, expectedResult));
}

TEST_CASE("Add double synonym group entries") {
	QueryResult result;

	string synonym1 = "a";
	unordered_set<string> entrySet1 = { "1", "2", "3", "4" };

	string synonym2 = "a1";
	unordered_set<string> entrySet2 = { "1", "2" };

	result.addSynonymGroup(synonym1, entrySet1);
	result.addSynonymGroup(synonym2, entrySet2);

	unordered_map<string, vector<string>> resultEntries = result.getResultMap();
	unordered_map<string, vector<string>> expectedResult = { { "a", { "1", "1", "2", "2", "3", "3", "4", "4" } },
															 { "a1", { "1", "2", "1", "2", "1", "2", "1", "2"} } };

	REQUIRE(checkResult(resultEntries, expectedResult));
}

TEST_CASE("Collapse double synoynm entries to single entry") {
	QueryResult result;

	string synonym1 = "a";
	unordered_set<string> entrySet1 = { "1", "2", "3", "4" };

	string synonym2 = "a1";
	unordered_set<string> entrySet2 = { "1", "2" };

	result.addSynonymGroup(synonym1, entrySet1);
	result.addSynonymGroup(synonym2, entrySet2);

	unordered_set<string> synonymSet = { synonym1 };
	result.collapseResult(synonymSet);

	unordered_map<string, vector<string>> resultEntries = result.getResultMap();
	unordered_map<string, vector<string>> expectedResult = { { "a", { "1", "2", "3", "4" } } };

	REQUIRE(checkResult(resultEntries, expectedResult));
}

TEST_CASE("Merge ___ into Empty Query Result") {
	SECTION("Single ClauseResult") {
		ClauseResult clauseResult;

		clauseResult.setClausePass();
		clauseResult.initializeSynonym("a");
		clauseResult.addEntry("1");
		clauseResult.addEntry("2");
		clauseResult.addEntry("4");
		clauseResult.addEntry("8");

		QueryResult queryResult;

		queryResult.mergeResult(clauseResult);

		unordered_map<string, vector<string>> resultEntries = queryResult.getResultMap();
        unordered_map<string, vector<string>> expectedResult = { { "a", { "1", "2", "4", "8" } } };

		REQUIRE(checkResult(resultEntries, expectedResult));
	}

	SECTION("Double ClauseResult") {
		ClauseResult clauseResult;

		clauseResult.setClausePass();
		clauseResult.initializeSynonym("a", "s");
		clauseResult.addEntry("1", "2");
		clauseResult.addEntry("1", "3");
		clauseResult.addEntry("2", "4");
		clauseResult.addEntry("4", "8");
		clauseResult.addEntry("4", "10");
		clauseResult.addEntry("4", "12");
		clauseResult.addEntry("8", "16");

		QueryResult queryResult;

		queryResult.mergeResult(clauseResult);

		unordered_map<string, vector<string>> resultEntries = queryResult.getResultMap();
		unordered_map<string, vector<string>> expectedResult = { { "a", { "1", "1", "2", "4", "4", "4", "8" } },
																 { "s", { "2", "3", "4", "8", "10", "12", "16" } } };

		REQUIRE(checkResult(resultEntries, expectedResult));
	}
}

TEST_CASE("Merge ___ into Single Query Result - Cross Product") {
	SECTION("Single ClauseResult") {
		ClauseResult clauseResult;

		clauseResult.setClausePass();
		clauseResult.initializeSynonym("a");
		clauseResult.addEntry("1");
		clauseResult.addEntry("2");
		clauseResult.addEntry("4");
		clauseResult.addEntry("8");

		QueryResult queryResult;

		string synonym = "s";
		unordered_set<string> entrySet = { "1", "2" };
		queryResult.addSynonymGroup(synonym, entrySet);

		queryResult.mergeResult(clauseResult);

		unordered_map<string, vector<string>> resultEntries = queryResult.getResultMap();
		unordered_map<string, vector<string>> expectedResult = { { "a", { "1", "2", "4", "8", "1", "2", "4", "8" } },
																 { "s", { "1", "1", "1", "1", "2", "2", "2", "2" } } };

		REQUIRE(checkResult(resultEntries, expectedResult));
	}

	SECTION("Double ClauseResult") {
		ClauseResult clauseResult;

		clauseResult.setClausePass();
		clauseResult.initializeSynonym("a", "a1");
		clauseResult.addEntry("1", "2");
		clauseResult.addEntry("1", "3");
		clauseResult.addEntry("2", "4");
		clauseResult.addEntry("4", "8");

		QueryResult queryResult;

		string synonym = "s";
		unordered_set<string> entrySet = { "1", "2" };
		queryResult.addSynonymGroup(synonym, entrySet);

		queryResult.mergeResult(clauseResult);

		unordered_map<string, vector<string>> resultEntries = queryResult.getResultMap();
		unordered_map<string, vector<string>> expectedResult = { { "a", { "1", "1", "2", "4", "1", "1", "2", "4" } },
																 { "a1", { "2", "3", "4", "8", "2", "3", "4", "8" } },
																 { "s", { "1", "1", "1", "1", "2", "2", "2", "2" } } };

		REQUIRE(checkResult(resultEntries, expectedResult));
	}
}

TEST_CASE("Merge ___ into Single Query Result - Single Filter") {
	SECTION("Single ClauseResult") {
		ClauseResult clauseResult;

		clauseResult.setClausePass();
		clauseResult.initializeSynonym("s");
		clauseResult.addEntry("1");
		clauseResult.addEntry("2");

		QueryResult queryResult;

		string synonym = "s";
		unordered_set<string> entrySet = { "1", "2", "4", "8" };
		queryResult.addSynonymGroup(synonym, entrySet);

		queryResult.mergeResult(clauseResult);

		unordered_map<string, vector<string>> resultEntries = queryResult.getResultMap();
		unordered_map<string, vector<string>> expectedResult = { { "s", { "1", "2" }}};

		REQUIRE(checkResult(resultEntries, expectedResult));
	}

	SECTION("Double ClauseResult") {
		ClauseResult clauseResult;

		clauseResult.setClausePass();
		clauseResult.initializeSynonym("s", "s1");
		clauseResult.addEntry("1", "2");
		clauseResult.addEntry("1", "3");

		QueryResult queryResult;

		string synonym = "s";
		unordered_set<string> entrySet = { "1", "2" };
		queryResult.addSynonymGroup(synonym, entrySet);

		queryResult.mergeResult(clauseResult);

		unordered_map<string, vector<string>> resultEntries = queryResult.getResultMap();
		unordered_map<string, vector<string>> expectedResult = { { "s",  { "1", "1" } },
																 { "s1", { "2", "3" } } };

		REQUIRE(checkResult(resultEntries, expectedResult));
	}
}

TEST_CASE("Merge ___ into Multiple Query Result") {
	SECTION("Double ClauseResult - Cross Product") {
		ClauseResult clauseResult;

		clauseResult.setClausePass();
		clauseResult.initializeSynonym("s", "s1");
		clauseResult.addEntry("1", "2");
		clauseResult.addEntry("1", "3");

		QueryResult queryResult;

		string synonym1 = "a";
		unordered_set<string> entrySet1 = { "1", "2", "3" };

		string synonym2 = "a1";
		unordered_set<string> entrySet2 = { "1", "2" };

		queryResult.addSynonymGroup(synonym1, entrySet1);
		queryResult.addSynonymGroup(synonym2, entrySet2);

		queryResult.mergeResult(clauseResult);

		unordered_map<string, vector<string>> resultEntries = queryResult.getResultMap();
		unordered_map<string, vector<string>> expectedResult = { { "a",  { "1", "1", "1", "1", "2", "2", "2", "2", "3", "3", "3", "3" } },
																 { "a1", { "1", "1", "2", "2", "1", "1", "2", "2", "1", "1", "2", "2" } },
																 { "s",  { "1", "1", "1", "1", "1", "1", "1", "1", "1", "1", "1", "1" } },
																 { "s1", { "2", "3", "2", "3", "2", "3", "2", "3", "2", "3", "2", "3" } } };

		REQUIRE(checkResult(resultEntries, expectedResult));
	}

	SECTION("Double ClauseResult - Cross Product & Filter") {
		ClauseResult clauseResult;

		clauseResult.setClausePass();
		clauseResult.initializeSynonym("a", "s");
		clauseResult.addEntry("1", "2");
		clauseResult.addEntry("1", "3");

		QueryResult queryResult;

		string synonym1 = "a";
		unordered_set<string> entrySet1 = { "1", "2", "3" };

		string synonym2 = "a1";
		unordered_set<string> entrySet2 = { "1", "2" };

		queryResult.addSynonymGroup(synonym1, entrySet1);
		queryResult.addSynonymGroup(synonym2, entrySet2);

		queryResult.mergeResult(clauseResult);

		unordered_map<string, vector<string>> resultEntries = queryResult.getResultMap();
		unordered_map<string, vector<string>> expectedResult = { { "a", { "1", "1", "1", "1" } },
																 { "a1", { "1", "1", "2", "2" } },
																 { "s", { "2", "3", "2", "3" } } };

		REQUIRE(checkResult(resultEntries, expectedResult));
	}
}
