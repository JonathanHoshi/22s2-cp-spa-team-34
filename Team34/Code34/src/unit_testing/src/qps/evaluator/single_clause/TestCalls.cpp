#include <memory>
#include <unordered_set>
#include <unordered_map>

#include "catch.hpp"
#include "qps/argument/entity/VariableEntity.h"
#include "qps/argument/entity/ProcedureEntity.h"
#include "qps/argument/entity/stmt/ReadStmtEntity.h"
#include "qps/argument/entity/stmt/CallStmtEntity.h"
#include "qps/argument/input/StringInput.h"
#include "qps/clause/strategy/relation/CallsStrategy.h"
#include "../stub_entity/StubConstProcVarGetter.cpp"
#include "../stub_entity/StubStmtGetter.cpp"
#include "../stub_clause/StubCallsGetter.cpp"
#include "../QueryFunction.h"

namespace test_calls_eval {

    StubCallsGetter callsInterface;
    StubStmtGetter stmtInterface;
    StubConstProcVarGetter constProcVarInterface;

    std::unordered_map<int, std::string> readMap = {{3, "sp"},
        {6, "qps"},
        {7, "pkb"}};
    std::unordered_map<int, std::string> callStmtMap = {{1, "cx"},
        {2, "ryan"},
        {4, "jon"},
        {5, "nat"},
        {8, "jon"}};
    std::unordered_set<std::string> varSet = {"pkb", "qps", "sp"};
    std::unordered_set<std::string> procSet = {"cx", "fred", "jon", "nat", "ryan"};
    std::unordered_map<std::string, std::unordered_set<std::string>> callsMapSet = {{"fred", {"cx", "ryan"}},
        {"cx", {"jon", "nat"}},
        {"ryan", {"jon"}}};

    std::unordered_map<std::string, std::unordered_set<std::string>> callsTMapSet = {{"fred", {"cx", "ryan", "jon", "nat"}},
        {"cx", {"jon", "nat"}},
        {"ryan", {"jon"}}};

    void initializeInterfaces() {
        callsInterface.setCallsEntries(callsMapSet);
        callsInterface.setCallsTEntries(callsTMapSet);
        constProcVarInterface.setVarEntries(varSet);
        constProcVarInterface.setProcEntries(procSet);
        stmtInterface.setReadStmtEntries(readMap);
        stmtInterface.setCallStmtEntries(callStmtMap);
    }
}

using namespace test_calls_eval;
using namespace query_func;

// stmt s, s1; assign a, a1; while w; if ifs; variable v, v1; 
// procedure p, p1; constant c; read re; print pn; call cl;

TEST_CASE("Evaluate Single Select - Single Calls") {
    initializeInterfaces();

    SECTION("Left Input") {
        SECTION("Calls('fred', p) - Output") {
            std::unordered_set<std::string> expectedResult = {"cx", "ryan"};
            std::vector<std::shared_ptr<Clause>> clauseList;

            std::shared_ptr<EntityArgument> selection = std::make_shared<ProcedureEntity>(&constProcVarInterface, "p", "");;
            std::shared_ptr<Argument> firstArg = std::make_shared<StringInput>("fred");
            std::shared_ptr<Argument> secondArg = std::make_shared<ProcedureEntity>(&constProcVarInterface, "p", "");;

            clauseList.push_back(std::make_shared<Clause>(std::make_shared<CallsStrategy>(&callsInterface), firstArg, secondArg));

            TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
        }

        SECTION("Calls('nat', p) - Empty") {
            std::unordered_set<std::string> expectedResult;
            std::vector<std::shared_ptr<Clause>> clauseList;

            std::shared_ptr<EntityArgument> selection = std::make_shared<ProcedureEntity>(&constProcVarInterface, "p", "");;
            std::shared_ptr<Argument> firstArg = std::make_shared<StringInput>("nat");
            std::shared_ptr<Argument> secondArg = std::make_shared<ProcedureEntity>(&constProcVarInterface, "p", "");;

            clauseList.push_back(std::make_shared<Clause>(std::make_shared<CallsStrategy>(&callsInterface), firstArg, secondArg));

            TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
        }

        SECTION("Calls*('fred', p) - Output") {
            std::unordered_set<std::string> expectedResult = {"jon", "nat", "ryan", "cx"};
            std::vector<std::shared_ptr<Clause>> clauseList;

            std::shared_ptr<EntityArgument> selection = std::make_shared<ProcedureEntity>(&constProcVarInterface, "p", "");;
            std::shared_ptr<Argument> firstArg = std::make_shared<StringInput>("fred");
            std::shared_ptr<Argument> secondArg = std::make_shared<ProcedureEntity>(&constProcVarInterface, "p", "");;

            clauseList.push_back(std::make_shared<Clause>(std::make_shared<CallsStrategy>(&callsInterface, true), firstArg, secondArg));

            TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
        }

        SECTION("Calls*('nat', p) - Empty") {
            std::unordered_set<std::string> expectedResult;
            std::vector<std::shared_ptr<Clause>> clauseList;

            std::shared_ptr<EntityArgument> selection = std::make_shared<ProcedureEntity>(&constProcVarInterface, "p", "");;
            std::shared_ptr<Argument> firstArg = std::make_shared<StringInput>("nat");
            std::shared_ptr<Argument> secondArg = std::make_shared<ProcedureEntity>(&constProcVarInterface, "p", "");;

            clauseList.push_back(std::make_shared<Clause>(std::make_shared<CallsStrategy>(&callsInterface, true), firstArg, secondArg));

            TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
        }
    }

    SECTION("Right Input") {
        SECTION("Calls(p, 'jon') - Output") {
            std::unordered_set<std::string> expectedResult = {"cx", "ryan"};
            std::vector<std::shared_ptr<Clause>> clauseList;

            std::shared_ptr<EntityArgument> selection = std::make_shared<ProcedureEntity>(&constProcVarInterface, "p", "");;
            std::shared_ptr<Argument> firstArg = std::make_shared<ProcedureEntity>(&constProcVarInterface, "p", "");;
            std::shared_ptr<Argument> secondArg = std::make_shared<StringInput>("jon");

            clauseList.push_back(std::make_shared<Clause>(std::make_shared<CallsStrategy>(&callsInterface), firstArg, secondArg));

            TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
        }

        SECTION("Calls(p, 'fred') - Empty") {
            std::unordered_set<std::string> expectedResult;
            std::vector<std::shared_ptr<Clause>> clauseList;

            std::shared_ptr<EntityArgument> selection = std::make_shared<ProcedureEntity>(&constProcVarInterface, "p", "");;
            std::shared_ptr<Argument> firstArg = std::make_shared<ProcedureEntity>(&constProcVarInterface, "p", "");;
            std::shared_ptr<Argument> secondArg = std::make_shared<StringInput>("fred");

            clauseList.push_back(std::make_shared<Clause>(std::make_shared<CallsStrategy>(&callsInterface), firstArg, secondArg));

            TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
        }

        SECTION("Calls*(p, 'jon') - Output") {
            std::unordered_set<std::string> expectedResult = {"fred", "cx", "ryan"};
            std::vector<std::shared_ptr<Clause>> clauseList;

            std::shared_ptr<EntityArgument> selection = std::make_shared<ProcedureEntity>(&constProcVarInterface, "p", "");;
            std::shared_ptr<Argument> firstArg = std::make_shared<ProcedureEntity>(&constProcVarInterface, "p", "");;
            std::shared_ptr<Argument> secondArg = std::make_shared<StringInput>("jon");

            clauseList.push_back(std::make_shared<Clause>(std::make_shared<CallsStrategy>(&callsInterface, true), firstArg, secondArg));

            TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
        }

        SECTION("Calls*(p, 'fred') - Empty") {
            std::unordered_set<std::string> expectedResult;
            std::vector<std::shared_ptr<Clause>> clauseList;

            std::shared_ptr<EntityArgument> selection = std::make_shared<ProcedureEntity>(&constProcVarInterface, "p", "");;
            std::shared_ptr<Argument> firstArg = std::make_shared<ProcedureEntity>(&constProcVarInterface, "p", "");;
            std::shared_ptr<Argument> secondArg = std::make_shared<StringInput>("fred");

            clauseList.push_back(std::make_shared<Clause>(std::make_shared<CallsStrategy>(&callsInterface, true), firstArg, secondArg));

            TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
        }
    }

    SECTION("Both Input") {
        SECTION("Calls('fred', 'cx')") {
            SECTION("Select p - Output") {
                std::unordered_set<std::string> expectedResult = procSet;
                std::vector<std::shared_ptr<Clause>> clauseList;

                std::shared_ptr<EntityArgument> selection = std::make_shared<ProcedureEntity>(&constProcVarInterface, "p", "");;
                std::shared_ptr<Argument> firstArg = std::make_shared<StringInput>("fred");
                std::shared_ptr<Argument> secondArg = std::make_shared<StringInput>("cx");

                clauseList.push_back(std::make_shared<Clause>(std::make_shared<CallsStrategy>(&callsInterface), firstArg, secondArg));

                TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
            }
        }

        SECTION("Calls*('fred', 'cx')") {
            SECTION("Select p - Output") {
                std::unordered_set<std::string> expectedResult = procSet;
                std::vector<std::shared_ptr<Clause>> clauseList;

                std::shared_ptr<EntityArgument> selection = std::make_shared<ProcedureEntity>(&constProcVarInterface, "p", "");;
                std::shared_ptr<Argument> firstArg = std::make_shared<StringInput>("fred");
                std::shared_ptr<Argument> secondArg = std::make_shared<StringInput>("cx");

                clauseList.push_back(std::make_shared<Clause>(std::make_shared<CallsStrategy>(&callsInterface, true), firstArg, secondArg));

                TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
            }
        }

        SECTION("Calls('fred', 'nat')") {
            SECTION("Select p - Empty") {
                std::unordered_set<std::string> expectedResult;
                std::vector<std::shared_ptr<Clause>> clauseList;

                std::shared_ptr<EntityArgument> selection = std::make_shared<ProcedureEntity>(&constProcVarInterface, "p", "");;
                std::shared_ptr<Argument> firstArg = std::make_shared<StringInput>("fred");
                std::shared_ptr<Argument> secondArg = std::make_shared<StringInput>("nat");

                clauseList.push_back(std::make_shared<Clause>(std::make_shared<CallsStrategy>(&callsInterface), firstArg, secondArg));

                TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
            }
        }

        SECTION("Calls*('fred', 'nat')") {
            SECTION("Select p - Output") {
                std::unordered_set<std::string> expectedResult = procSet;
                std::vector<std::shared_ptr<Clause>> clauseList;

                std::shared_ptr<EntityArgument> selection = std::make_shared<ProcedureEntity>(&constProcVarInterface, "p", "");;
                std::shared_ptr<Argument> firstArg = std::make_shared<StringInput>("fred");
                std::shared_ptr<Argument> secondArg = std::make_shared<StringInput>("nat");

                clauseList.push_back(std::make_shared<Clause>(std::make_shared<CallsStrategy>(&callsInterface, true), firstArg, secondArg));

                TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
            }
        }

        SECTION("Calls*('nat', 'fred')") {
            SECTION("Select s - Empty") {
                std::unordered_set<std::string> expectedResult;
                std::vector<std::shared_ptr<Clause>> clauseList;

                std::shared_ptr<EntityArgument> selection = std::make_shared<ProcedureEntity>(&constProcVarInterface, "p", "");;
                std::shared_ptr<Argument> firstArg = std::make_shared<StringInput>("nat");
                std::shared_ptr<Argument> secondArg = std::make_shared<StringInput>("fred");

                clauseList.push_back(std::make_shared<Clause>(std::make_shared<CallsStrategy>(&callsInterface, true), firstArg, secondArg));

                TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
            }
        }
    }

    SECTION("No Input") {
        SECTION("Calls(p, p1)") {
            SECTION("Select p - Output") {
                std::unordered_set<std::string> expectedResult = {"fred", "cx", "ryan"};
                std::vector<std::shared_ptr<Clause>> clauseList;

                std::shared_ptr<EntityArgument> selection = std::make_shared<ProcedureEntity>(&constProcVarInterface, "p", "");;
                std::shared_ptr<Argument> firstArg = std::make_shared<ProcedureEntity>(&constProcVarInterface, "p", "");;
                std::shared_ptr<Argument> secondArg = std::make_shared<ProcedureEntity>(&constProcVarInterface, "p1", "");;;

                clauseList.push_back(std::make_shared<Clause>(std::make_shared<CallsStrategy>(&callsInterface), firstArg, secondArg));

                TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
            }

            SECTION("Select p1 - Output") {
                std::unordered_set<std::string> expectedResult = {"cx", "ryan", "nat", "jon"};
                std::vector<std::shared_ptr<Clause>> clauseList;

                std::shared_ptr<EntityArgument> selection = std::make_shared<ProcedureEntity>(&constProcVarInterface, "p1", "");;;
                std::shared_ptr<Argument> firstArg = std::make_shared<ProcedureEntity>(&constProcVarInterface, "p", "");;
                std::shared_ptr<Argument> secondArg = std::make_shared<ProcedureEntity>(&constProcVarInterface, "p1", "");;;

                clauseList.push_back(std::make_shared<Clause>(std::make_shared<CallsStrategy>(&callsInterface), firstArg, secondArg));

                TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
            }
        }

        SECTION("Calls*(p, p1)") {
            SECTION("Select s - Output") {
                std::unordered_set<std::string> expectedResult = {"fred", "cx", "ryan"};
                std::vector<std::shared_ptr<Clause>> clauseList;

                std::shared_ptr<EntityArgument> selection = std::make_shared<ProcedureEntity>(&constProcVarInterface, "p", "");;
                std::shared_ptr<Argument> firstArg = std::make_shared<ProcedureEntity>(&constProcVarInterface, "p", "");;
                std::shared_ptr<Argument> secondArg = std::make_shared<ProcedureEntity>(&constProcVarInterface, "p1", "");;;

                clauseList.push_back(std::make_shared<Clause>(std::make_shared<CallsStrategy>(&callsInterface, true), firstArg, secondArg));

                TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
            }

            SECTION("Select s1 - Output") {
                std::unordered_set<std::string> expectedResult = {"cx", "ryan", "nat", "jon"};
                std::vector<std::shared_ptr<Clause>> clauseList;

                std::shared_ptr<EntityArgument> selection = std::make_shared<ProcedureEntity>(&constProcVarInterface, "p1", "");;;
                std::shared_ptr<Argument> firstArg = std::make_shared<ProcedureEntity>(&constProcVarInterface, "p", "");;
                std::shared_ptr<Argument> secondArg = std::make_shared<ProcedureEntity>(&constProcVarInterface, "p1", "");;;

                clauseList.push_back(std::make_shared<Clause>(std::make_shared<CallsStrategy>(&callsInterface, true), firstArg, secondArg));

                TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
            }
        }
    }
}
