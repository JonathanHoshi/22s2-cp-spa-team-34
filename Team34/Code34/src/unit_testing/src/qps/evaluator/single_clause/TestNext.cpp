#include <memory>
#include <unordered_map>
#include <unordered_set>

#include "catch.hpp"
#include "qps/argument/entity/VariableEntity.h"
#include "qps/argument/entity/ProcedureEntity.h"
#include "qps/argument/entity/stmt/StmtEntity.h"
#include "qps/argument/entity/stmt/ReadStmtEntity.h"
#include "qps/argument/input/IntInput.h"
#include "qps/clause/strategy/relation/NextStrategy.h"

#include "../stub_entity/StubConstProcVarGetter.cpp"
#include "../stub_entity/StubStmtGetter.cpp"
#include "../stub_clause/StubNextGetter.cpp"
#include "../QueryFunction.h"

namespace test_next_eval
{
	StubNextGetter nextInterface;
	StubStmtGetter stmtInterface;
	StubConstProcVarGetter constProcVarInterface;

	unordered_map<int, string> callMap = { { 5, "fred" } };
	unordered_map<int, string> readMap = { { 7, "s" } };
	unordered_map<int, string> printMap = { { 2, "x" },
											{ 9, "j" }};

	unordered_set<int> ifStmtSet = { 11 };
	unordered_set<int> whileStmtSet = { 13 };
	unordered_set<int> assignStmtSet = { 1, 3, 4, 6, 8, 9, 10, 12, 14 };
	unordered_set<string> varSet = { "s", "b", "j", "k", "l", "x", "y" };
	unordered_set<string> procSet = { "cx", "fred", "jon", "nat" };
	unordered_map<int, unordered_set<int>> nextMapSet = { { 1, { 2 } },
														  { 2, { 3 } },
														  { 4, { 5 } },
														  { 5, { 6 } },
														  { 8, { 9 } },
														  { 9, { 10 } },
														  { 10, { 11 } },
														  { 11, { 12, 13 } },
														  { 13, { 14 } },
														  { 14, { 13 } } };

	unordered_map<int, unordered_set<int>> nextTMapSet = { { 1, { 2, 3 } },
														   { 2, { 3 } },
														   { 4, { 5, 6 } },
														   { 5, { 6 } },
														   { 8, { 9, 10, 11, 12, 13, 14 } },
														   { 9, { 10, 11, 12, 13 , 14 } },
														   { 10, { 11, 12, 13, 14 } },
														   { 11, { 12, 13, 14 } },
														   { 13, { 13, 14 } },
														   { 14, { 13, 14 } } };

	// for result
	unordered_set<int> stmtSet = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };

	void initializeInterfaces()
	{
		nextInterface.setNextEntries(nextMapSet);
		nextInterface.setNextTEntries(nextTMapSet);
		constProcVarInterface.setVarEntries(varSet);
		constProcVarInterface.setProcEntries(procSet);
		stmtInterface.setReadStmtEntries(readMap);
		stmtInterface.setPrintStmtEntries(printMap);
		stmtInterface.setAssignStmtEntries(assignStmtSet);
		stmtInterface.setIfStmtEntries(ifStmtSet);
		stmtInterface.setWhileStmtEntries(whileStmtSet);
		stmtInterface.setCallStmtEntries(callMap);
	}
}

using namespace test_next_eval;
using namespace query_func;

// stmt s, s1; assign a, s1; while w; if ifs; variable v, v1; 
// procedure p, p1; constant c; read re; print pn; call cl;

TEST_CASE("Evaluate Single Select - Single Next") {
	initializeInterfaces();
	SECTION("Left Input") {
		SECTION("Next(1, s) - Output") {
			unordered_set<string> expectedResult = { "2" };
			vector<shared_ptr<Clause>> clauseList;

			shared_ptr<EntityArgument> selection = make_shared<StmtStmtEntity>(&stmtInterface, "s", "");
			shared_ptr<Argument> firstArg = make_shared<IntInput>("1");
			shared_ptr<Argument> secondArg = make_shared<StmtStmtEntity>(&stmtInterface, "s", "");

			clauseList.push_back(make_shared<Clause>(make_shared<NextStrategy>(&nextInterface), firstArg, secondArg));

			TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
		}

		SECTION("Next(3, s) - Empty") {
			unordered_set<string> expectedResult;
			vector<shared_ptr<Clause>> clauseList;

			shared_ptr<EntityArgument> selection = make_shared<StmtStmtEntity>(&stmtInterface, "s", "");
			shared_ptr<Argument> firstArg = make_shared<IntInput>("3");
			shared_ptr<Argument> secondArg = make_shared<StmtStmtEntity>(&stmtInterface, "s", "");

			clauseList.push_back(make_shared<Clause>(make_shared<NextStrategy>(&nextInterface), firstArg, secondArg));

			TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
		}

		SECTION("Next*(8, s) - Output") {
			unordered_set<string> expectedResult = { "9", "10", "11", "12", "13", "14" };
			vector<shared_ptr<Clause>> clauseList;

			shared_ptr<EntityArgument> selection = make_shared<StmtStmtEntity>(&stmtInterface, "s", "");
			shared_ptr<Argument> firstArg = make_shared<IntInput>("8");
			shared_ptr<Argument> secondArg = make_shared<StmtStmtEntity>(&stmtInterface, "s", "");

			clauseList.push_back(make_shared<Clause>(make_shared<NextStrategy>(&nextInterface, true), firstArg, secondArg));

			TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
		}

		SECTION("Next*(3, s) - Empty") {
			unordered_set<string> expectedResult;
			vector<shared_ptr<Clause>> clauseList;

			shared_ptr<EntityArgument> selection = make_shared<StmtStmtEntity>(&stmtInterface, "s", "");
			shared_ptr<Argument> firstArg = make_shared<IntInput>("3");
			shared_ptr<Argument> secondArg = make_shared<StmtStmtEntity>(&stmtInterface, "s", "");

			clauseList.push_back(make_shared<Clause>(make_shared<NextStrategy>(&nextInterface, true), firstArg, secondArg));

			TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
		}
	}

	SECTION("Right Input") {
		SECTION("Next(s, 3) - Output") {
			unordered_set<string> expectedResult = { "2" };
			vector<shared_ptr<Clause>> clauseList;

			shared_ptr<EntityArgument> selection = make_shared<StmtStmtEntity>(&stmtInterface, "s", "");
			shared_ptr<Argument> firstArg = make_shared<StmtStmtEntity>(&stmtInterface, "s", "");
			shared_ptr<Argument> secondArg = make_shared<IntInput>("3");

			clauseList.push_back(make_shared<Clause>(make_shared<NextStrategy>(&nextInterface), firstArg, secondArg));

			TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
		}

		SECTION("Next(s, 1) - Empty") {
			unordered_set<string> expectedResult;
			vector<shared_ptr<Clause>> clauseList;

			shared_ptr<EntityArgument> selection = make_shared<StmtStmtEntity>(&stmtInterface, "s", "");
			shared_ptr<Argument> firstArg = make_shared<StmtStmtEntity>(&stmtInterface, "s", "");
			shared_ptr<Argument> secondArg = make_shared<IntInput>("1");

			clauseList.push_back(make_shared<Clause>(make_shared<NextStrategy>(&nextInterface), firstArg, secondArg));

			TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
		}

		SECTION("Next*(s, 12) - Output") {
			unordered_set<string> expectedResult = { "8", "9", "10", "11" };
			vector<shared_ptr<Clause>> clauseList;

			shared_ptr<EntityArgument> selection = make_shared<StmtStmtEntity>(&stmtInterface, "s", "");
			shared_ptr<Argument> firstArg = make_shared<StmtStmtEntity>(&stmtInterface, "s", "");
			shared_ptr<Argument> secondArg = make_shared<IntInput>("12");

			clauseList.push_back(make_shared<Clause>(make_shared<NextStrategy>(&nextInterface, true), firstArg, secondArg));

			TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
		}

		SECTION("Next*(s, 4) - Empty") {
			unordered_set<string> expectedResult;
			vector<shared_ptr<Clause>> clauseList;

			shared_ptr<EntityArgument> selection = make_shared<StmtStmtEntity>(&stmtInterface, "s", "");
			shared_ptr<Argument> firstArg = make_shared<StmtStmtEntity>(&stmtInterface, "s", "");
			shared_ptr<Argument> secondArg = make_shared<IntInput>("4");

			clauseList.push_back(make_shared<Clause>(make_shared<NextStrategy>(&nextInterface, true), firstArg, secondArg));

			TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
		}
	}

	SECTION("Both Input") {
		SECTION("Next(1, 2)") {
			SECTION("Select a - Output") {
				unordered_set<string> expectedResult = ConversionUtils::convertIntToStringSet(stmtSet);
				vector<shared_ptr<Clause>> clauseList;

				shared_ptr<EntityArgument> selection = make_shared<StmtStmtEntity>(&stmtInterface, "s", "");
				shared_ptr<Argument> firstArg = make_shared<IntInput>("1");
				shared_ptr<Argument> secondArg = make_shared<IntInput>("2");

				clauseList.push_back(make_shared<Clause>(make_shared<NextStrategy>(&nextInterface), firstArg, secondArg));

				TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
			}
		}

		SECTION("Next*(1, 2)") {
			SECTION("Select s - Output") {
				unordered_set<string> expectedResult = ConversionUtils::convertIntToStringSet(stmtSet);
				vector<shared_ptr<Clause>> clauseList;

				shared_ptr<EntityArgument> selection = make_shared<StmtStmtEntity>(&stmtInterface, "s", "");
				shared_ptr<Argument> firstArg = make_shared<IntInput>("1");
				shared_ptr<Argument> secondArg = make_shared<IntInput>("2");

				clauseList.push_back(make_shared<Clause>(make_shared<NextStrategy>(&nextInterface, true), firstArg, secondArg));

				TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
			}
		}

		SECTION("Next(8, 12)") {
			SECTION("Select s - Empty") {
				unordered_set<string> expectedResult;
				vector<shared_ptr<Clause>> clauseList;

				shared_ptr<EntityArgument> selection = make_shared<StmtStmtEntity>(&stmtInterface, "s", "");
				shared_ptr<Argument> firstArg = make_shared<IntInput>("8");
				shared_ptr<Argument> secondArg = make_shared<IntInput>("12");

				clauseList.push_back(make_shared<Clause>(make_shared<NextStrategy>(&nextInterface), firstArg, secondArg));

				TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
			}
		}

		SECTION("Next*(8, 12)") {
			SECTION("Select s - Output") {
				unordered_set<string> expectedResult = ConversionUtils::convertIntToStringSet(stmtSet);
				vector<shared_ptr<Clause>> clauseList;

				shared_ptr<EntityArgument> selection = make_shared<StmtStmtEntity>(&stmtInterface, "s", "");
				shared_ptr<Argument> firstArg = make_shared<IntInput>("8");
				shared_ptr<Argument> secondArg = make_shared<IntInput>("12");

				clauseList.push_back(make_shared<Clause>(make_shared<NextStrategy>(&nextInterface, true), firstArg, secondArg));

				TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
			}
		}

		SECTION("Next*(3, 4)") {
			SECTION("Select s - Empty") {
				unordered_set<string> expectedResult;
				vector<shared_ptr<Clause>> clauseList;

				shared_ptr<EntityArgument> selection = make_shared<StmtStmtEntity>(&stmtInterface, "s", "");
				shared_ptr<Argument> firstArg = make_shared<IntInput>("3");
				shared_ptr<Argument> secondArg = make_shared<IntInput>("4");

				clauseList.push_back(make_shared<Clause>(make_shared<NextStrategy>(&nextInterface, true), firstArg, secondArg));

				TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
			}
		}
	}

	SECTION("No Input") {
		SECTION("Next(s, s1)") {
			SECTION("Select s - Output") {
				unordered_set<string> expectedResult = { "1", "2", "4", "5", "8", "9", "10", "11", "13", "14" };
				vector<shared_ptr<Clause>> clauseList;

				shared_ptr<EntityArgument> selection = make_shared<StmtStmtEntity>(&stmtInterface, "s", "");
				shared_ptr<Argument> firstArg = make_shared<StmtStmtEntity>(&stmtInterface, "s", "");
				shared_ptr<Argument> secondArg = make_shared<StmtStmtEntity>(&stmtInterface, "s1", "");

				clauseList.push_back(make_shared<Clause>(make_shared<NextStrategy>(&nextInterface), firstArg, secondArg));

				TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
			}

			SECTION("Select s1 - Output") {
				unordered_set<string> expectedResult = { "2", "3", "5", "6", "9", "10", "11", "12", "13", "14" };
				vector<shared_ptr<Clause>> clauseList;

				shared_ptr<EntityArgument> selection = make_shared<StmtStmtEntity>(&stmtInterface, "s1", "");
				shared_ptr<Argument> firstArg = make_shared<StmtStmtEntity>(&stmtInterface, "s", "");
				shared_ptr<Argument> secondArg = make_shared<StmtStmtEntity>(&stmtInterface, "s1", "");

				clauseList.push_back(make_shared<Clause>(make_shared<NextStrategy>(&nextInterface), firstArg, secondArg));

				TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
			}
		}

		SECTION("Next*(s, s1)") {
			SECTION("Select s - Output") {
				unordered_set<string> expectedResult = { "1", "2", "4", "5", "8", "9", "10", "11", "13", "14" };
				vector<shared_ptr<Clause>> clauseList;

				shared_ptr<EntityArgument> selection = make_shared<StmtStmtEntity>(&stmtInterface, "s", "");
				shared_ptr<Argument> firstArg = make_shared<StmtStmtEntity>(&stmtInterface, "s", "");
				shared_ptr<Argument> secondArg = make_shared<StmtStmtEntity>(&stmtInterface, "s1", "");

				clauseList.push_back(make_shared<Clause>(make_shared<NextStrategy>(&nextInterface, true), firstArg, secondArg));

				TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
			}

			SECTION("Select s1 - Output") {
				unordered_set<string> expectedResult = { "2", "3", "5", "6", "9", "10", "11", "12", "13", "14" };
				vector<shared_ptr<Clause>> clauseList;

				shared_ptr<EntityArgument> selection = make_shared<StmtStmtEntity>(&stmtInterface, "s1", "");
				shared_ptr<Argument> firstArg = make_shared<StmtStmtEntity>(&stmtInterface, "s", "");
				shared_ptr<Argument> secondArg = make_shared<StmtStmtEntity>(&stmtInterface, "s1", "");

				clauseList.push_back(make_shared<Clause>(make_shared<NextStrategy>(&nextInterface, true), firstArg, secondArg));

				TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
			}
		}

		SECTION("Next*(s, s)") {
			unordered_set<string> expectedResult = { "13", "14" };
			vector<shared_ptr<Clause>> clauseList;

			shared_ptr<EntityArgument> selection = make_shared<StmtStmtEntity>(&stmtInterface, "s", "");
			shared_ptr<Argument> firstArg = make_shared<StmtStmtEntity>(&stmtInterface, "s", "");
			shared_ptr<Argument> secondArg = make_shared<StmtStmtEntity>(&stmtInterface, "s", "");

			clauseList.push_back(make_shared<Clause>(make_shared<NextStrategy>(&nextInterface, true), firstArg, secondArg));

			TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
		}
	}
}
