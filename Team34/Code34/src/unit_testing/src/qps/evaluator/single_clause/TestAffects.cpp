#include <memory>
#include <unordered_map>
#include <unordered_set>

#include "catch.hpp"
#include "qps/argument/entity/VariableEntity.h"
#include "qps/argument/entity/ProcedureEntity.h"
#include "qps/argument/entity/stmt/AssignStmtEntity.h"
#include "qps/argument/entity/stmt/ReadStmtEntity.h"
#include "qps/argument/input/IntInput.h"
#include "qps/clause/strategy/relation/AffectsStrategy.h"

#include "../stub_entity/StubConstProcVarGetter.cpp"
#include "../stub_entity/StubStmtGetter.cpp"
#include "../stub_clause/StubAffectsGetter.cpp"
#include "../QueryFunction.h"

namespace test_affects_eval
{
	StubAffectsGetter affectsInterface;
	StubStmtGetter stmtInterface;
	StubConstProcVarGetter constProcVarInterface;

	unordered_map<int, string> readMap = { { 7, "a" } };
	unordered_map<int, string> printMap = { { 2, "x" },
											{ 9, "j" }};

	unordered_set<int> ifStmtMap = { 11 };
	unordered_set<int> whileStmtMap = { 13 };
	unordered_set<int> assignStmtSet = { 1, 3, 4, 6, 8, 9, 10, 12, 14 };
	unordered_set<string> varSet = { "a", "b", "j", "k", "l", "x", "y" };
	unordered_set<string> procSet = { "cx", "fred", "jon", "nat" };
	unordered_map<int, unordered_set<int>> affectsMapSet = { { 1, { 3 } },
															 { 8, { 10 } },
															 { 10, { 12, 14 } },
															 { 14, { 14 } } };

	unordered_map<int, unordered_set<int>> affectsTMapSet = { { 1, { 3 } },
															  { 8, { 10, 12, 14 } },
															  { 10, { 12, 14 } },
															  { 14, { 14 } } };

	void initializeInterfaces()
	{
		affectsInterface.setAffectsEntries(affectsMapSet);
		affectsInterface.setAffectsTEntries(affectsTMapSet);
		constProcVarInterface.setVarEntries(varSet);
		constProcVarInterface.setProcEntries(procSet);
		stmtInterface.setReadStmtEntries(readMap);
		stmtInterface.setPrintStmtEntries(printMap);
		stmtInterface.setAssignStmtEntries(assignStmtSet);
		stmtInterface.setIfStmtEntries(ifStmtMap);
		stmtInterface.setWhileStmtEntries(whileStmtMap);
	}
}

using namespace test_affects_eval;
using namespace query_func;

// stmt s, s1; assign a, a1; while w; if ifs; variable v, v1; 
// procedure p, p1; constant c; read re; print pn; call cl;

TEST_CASE("Evaluate Single Select - Single Affects") {
	initializeInterfaces();
	SECTION("Left Input") {
		SECTION("Affects(1, a) - Output") {
			unordered_set<string> expectedResult = { "3" };
			vector<shared_ptr<Clause>> clauseList;

			shared_ptr<EntityArgument> selection = make_shared<AssignStmtEntity>(&stmtInterface, "a", "");
			shared_ptr<Argument> firstArg = make_shared<IntInput>("1");
			shared_ptr<Argument> secondArg = make_shared<AssignStmtEntity>(&stmtInterface, "a", "");

			clauseList.push_back(make_shared<Clause>(make_shared<AffectsStrategy>(&affectsInterface), firstArg, secondArg));

			TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
		}

		SECTION("Affects(3, a) - Empty") {
			unordered_set<string> expectedResult;
			vector<shared_ptr<Clause>> clauseList;

			shared_ptr<EntityArgument> selection = make_shared<AssignStmtEntity>(&stmtInterface, "a", "");
			shared_ptr<Argument> firstArg = make_shared<IntInput>("3");
			shared_ptr<Argument> secondArg = make_shared<AssignStmtEntity>(&stmtInterface, "a", "");

			clauseList.push_back(make_shared<Clause>(make_shared<AffectsStrategy>(&affectsInterface), firstArg, secondArg));

			TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
		}

		SECTION("Affects*(8, a) - Output") {
			unordered_set<string> expectedResult = { "10", "12", "14"};
			vector<shared_ptr<Clause>> clauseList;

			shared_ptr<EntityArgument> selection = make_shared<AssignStmtEntity>(&stmtInterface, "a", "");
			shared_ptr<Argument> firstArg = make_shared<IntInput>("8");
			shared_ptr<Argument> secondArg = make_shared<AssignStmtEntity>(&stmtInterface, "a", "");

			clauseList.push_back(make_shared<Clause>(make_shared<AffectsStrategy>(&affectsInterface, true), firstArg, secondArg));

			TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
		}

		SECTION("Affects*(3, a) - Empty") {
			unordered_set<string> expectedResult;
			vector<shared_ptr<Clause>> clauseList;

			shared_ptr<EntityArgument> selection = make_shared<AssignStmtEntity>(&stmtInterface, "a", "");
			shared_ptr<Argument> firstArg = make_shared<IntInput>("3");
			shared_ptr<Argument> secondArg = make_shared<AssignStmtEntity>(&stmtInterface, "a", "");

			clauseList.push_back(make_shared<Clause>(make_shared<AffectsStrategy>(&affectsInterface, true), firstArg, secondArg));

			TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
		}
	}

	SECTION("Right Input") {
		SECTION("Affects(a, 3) - Output") {
			unordered_set<string> expectedResult = { "1" };
			vector<shared_ptr<Clause>> clauseList;

			shared_ptr<EntityArgument> selection = make_shared<AssignStmtEntity>(&stmtInterface, "a", "");
			shared_ptr<Argument> firstArg = make_shared<AssignStmtEntity>(&stmtInterface, "a", "");
			shared_ptr<Argument> secondArg = make_shared<IntInput>("3");

			clauseList.push_back(make_shared<Clause>(make_shared<AffectsStrategy>(&affectsInterface), firstArg, secondArg));

			TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
		}

		SECTION("Affects(a, 1) - Empty") {
			unordered_set<string> expectedResult;
			vector<shared_ptr<Clause>> clauseList;

			shared_ptr<EntityArgument> selection = make_shared<AssignStmtEntity>(&stmtInterface, "a", "");
			shared_ptr<Argument> firstArg = make_shared<AssignStmtEntity>(&stmtInterface, "a", "");
			shared_ptr<Argument> secondArg = make_shared<IntInput>("1");

			clauseList.push_back(make_shared<Clause>(make_shared<AffectsStrategy>(&affectsInterface), firstArg, secondArg));

			TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
		}

		SECTION("Affects*(s, 12) - Output") {
			unordered_set<string> expectedResult = { "8", "10" };
			vector<shared_ptr<Clause>> clauseList;

			shared_ptr<EntityArgument> selection = make_shared<AssignStmtEntity>(&stmtInterface, "a", "");
			shared_ptr<Argument> firstArg = make_shared<AssignStmtEntity>(&stmtInterface, "a", "");
			shared_ptr<Argument> secondArg = make_shared<IntInput>("12");

			clauseList.push_back(make_shared<Clause>(make_shared<AffectsStrategy>(&affectsInterface, true), firstArg, secondArg));

			TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
		}

		SECTION("Affects*(a, 4) - Empty") {
			unordered_set<string> expectedResult;
			vector<shared_ptr<Clause>> clauseList;

			shared_ptr<EntityArgument> selection = make_shared<AssignStmtEntity>(&stmtInterface, "a", "");
			shared_ptr<Argument> firstArg = make_shared<AssignStmtEntity>(&stmtInterface, "a", "");
			shared_ptr<Argument> secondArg = make_shared<IntInput>("4");

			clauseList.push_back(make_shared<Clause>(make_shared<AffectsStrategy>(&affectsInterface, true), firstArg, secondArg));

			TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
		}
	}

	SECTION("Both Input") {
		SECTION("Affects(1, 3)") {
			SECTION("Select a - Output") {
				unordered_set<string> expectedResult = ConversionUtils::convertIntToStringSet(assignStmtSet);
				vector<shared_ptr<Clause>> clauseList;

				shared_ptr<EntityArgument> selection = make_shared<AssignStmtEntity>(&stmtInterface, "a", "");
				shared_ptr<Argument> firstArg = make_shared<IntInput>("1");
				shared_ptr<Argument> secondArg = make_shared<IntInput>("3");

				clauseList.push_back(make_shared<Clause>(make_shared<AffectsStrategy>(&affectsInterface), firstArg, secondArg));

				TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
			}
		}

		SECTION("Affects*(1, 3)") {
			SECTION("Select s - Output") {
				unordered_set<string> expectedResult = ConversionUtils::convertIntToStringSet(assignStmtSet);
				vector<shared_ptr<Clause>> clauseList;

				shared_ptr<EntityArgument> selection = make_shared<AssignStmtEntity>(&stmtInterface, "a", "");
				shared_ptr<Argument> firstArg = make_shared<IntInput>("1");
				shared_ptr<Argument> secondArg = make_shared<IntInput>("3");

				clauseList.push_back(make_shared<Clause>(make_shared<AffectsStrategy>(&affectsInterface, true), firstArg, secondArg));

				TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
			}
		}

		SECTION("Affects(8, 12)") {
			SECTION("Select s - Empty") {
				unordered_set<string> expectedResult;
				vector<shared_ptr<Clause>> clauseList;

				shared_ptr<EntityArgument> selection = make_shared<AssignStmtEntity>(&stmtInterface, "a", "");
				shared_ptr<Argument> firstArg = make_shared<IntInput>("8");
				shared_ptr<Argument> secondArg = make_shared<IntInput>("12");

				clauseList.push_back(make_shared<Clause>(make_shared<AffectsStrategy>(&affectsInterface), firstArg, secondArg));

				TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
			}
		}

		SECTION("Affects*(8, 12)") {
			SECTION("Select s - Output") {
				unordered_set<string> expectedResult = ConversionUtils::convertIntToStringSet(assignStmtSet);
				vector<shared_ptr<Clause>> clauseList;

				shared_ptr<EntityArgument> selection = make_shared<AssignStmtEntity>(&stmtInterface, "a", "");
				shared_ptr<Argument> firstArg = make_shared<IntInput>("8");
				shared_ptr<Argument> secondArg = make_shared<IntInput>("12");

				clauseList.push_back(make_shared<Clause>(make_shared<AffectsStrategy>(&affectsInterface, true), firstArg, secondArg));

				TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
			}
		}

		SECTION("Affects*(9, 10)") {
			SECTION("Select s - Empty") {
				unordered_set<string> expectedResult;
				vector<shared_ptr<Clause>> clauseList;

				shared_ptr<EntityArgument> selection = make_shared<AssignStmtEntity>(&stmtInterface, "s", "");
				shared_ptr<Argument> firstArg = make_shared<IntInput>("9");
				shared_ptr<Argument> secondArg = make_shared<IntInput>("10");

				clauseList.push_back(make_shared<Clause>(make_shared<AffectsStrategy>(&affectsInterface, true), firstArg, secondArg));

				TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
			}
		}
	}

	SECTION("No Input") {
		SECTION("Affects(a, a1)") {
			SECTION("Select a - Output") {
				unordered_set<string> expectedResult = { "1", "8", "10", "14" };
				vector<shared_ptr<Clause>> clauseList;

				shared_ptr<EntityArgument> selection = make_shared<AssignStmtEntity>(&stmtInterface, "a", "");
				shared_ptr<Argument> firstArg = make_shared<AssignStmtEntity>(&stmtInterface, "a", "");
				shared_ptr<Argument> secondArg = make_shared<AssignStmtEntity>(&stmtInterface, "a1", "");

				clauseList.push_back(make_shared<Clause>(make_shared<AffectsStrategy>(&affectsInterface), firstArg, secondArg));

				TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
			}

			SECTION("Select a1 - Output") {
				unordered_set<string> expectedResult = { "3", "10", "12", "14" };
				vector<shared_ptr<Clause>> clauseList;

				shared_ptr<EntityArgument> selection = make_shared<AssignStmtEntity>(&stmtInterface, "a1", "");
				shared_ptr<Argument> firstArg = make_shared<AssignStmtEntity>(&stmtInterface, "a", "");
				shared_ptr<Argument> secondArg = make_shared<AssignStmtEntity>(&stmtInterface, "a1", "");

				clauseList.push_back(make_shared<Clause>(make_shared<AffectsStrategy>(&affectsInterface), firstArg, secondArg));

				TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
			}
		}

		SECTION("Affects*(a, a1)") {
			SECTION("Select a - Output") {
				unordered_set<string> expectedResult = { "1", "8", "10", "14" };
				vector<shared_ptr<Clause>> clauseList;

				shared_ptr<EntityArgument> selection = make_shared<AssignStmtEntity>(&stmtInterface, "a", "");
				shared_ptr<Argument> firstArg = make_shared<AssignStmtEntity>(&stmtInterface, "a", "");
				shared_ptr<Argument> secondArg = make_shared<AssignStmtEntity>(&stmtInterface, "a1", "");

				clauseList.push_back(make_shared<Clause>(make_shared<AffectsStrategy>(&affectsInterface, true), firstArg, secondArg));

				TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
			}

			SECTION("Select s1 - Output") {
				unordered_set<string> expectedResult = { "3", "10", "12", "14" };
				vector<shared_ptr<Clause>> clauseList;

				shared_ptr<EntityArgument> selection = make_shared<AssignStmtEntity>(&stmtInterface, "a1", "");
				shared_ptr<Argument> firstArg = make_shared<AssignStmtEntity>(&stmtInterface, "a", "");
				shared_ptr<Argument> secondArg = make_shared<AssignStmtEntity>(&stmtInterface, "a1", "");

				clauseList.push_back(make_shared<Clause>(make_shared<AffectsStrategy>(&affectsInterface, true), firstArg, secondArg));

				TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
			}
		}

		SECTION("Affects*(a, a)") {
			unordered_set<string> expectedResult = { "14" };
			vector<shared_ptr<Clause>> clauseList;

			shared_ptr<EntityArgument> selection = make_shared<AssignStmtEntity>(&stmtInterface, "a", "");
			shared_ptr<Argument> firstArg = make_shared<AssignStmtEntity>(&stmtInterface, "a", "");
			shared_ptr<Argument> secondArg = make_shared<AssignStmtEntity>(&stmtInterface, "a", "");

			clauseList.push_back(make_shared<Clause>(make_shared<AffectsStrategy>(&affectsInterface, true), firstArg, secondArg));

			TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
		}
	}
}
