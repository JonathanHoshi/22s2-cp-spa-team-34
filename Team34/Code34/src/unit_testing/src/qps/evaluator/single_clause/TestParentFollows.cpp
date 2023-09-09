#include <memory>
#include <unordered_map>
#include <unordered_set>

#include "catch.hpp"
#include "qps/argument/entity/VariableEntity.h"
#include "qps/argument/entity/ProcedureEntity.h"
#include "qps/argument/entity/stmt/ReadStmtEntity.h"
#include "qps/argument/entity/stmt/StmtStmtEntity.h"
#include "qps/argument/input/IntInput.h"
#include "qps/clause/strategy/relation/FollowsStrategy.h"
#include "qps/clause/strategy/relation/ParentStrategy.h"

#include "../stub_entity/StubConstProcVarGetter.cpp"
#include "../stub_entity/StubStmtGetter.cpp"
#include "../stub_clause/StubFollowsGetter.cpp"
#include "../stub_clause/StubParentGetter.cpp"
#include "../QueryFunction.h"

namespace test_parentfollows_eval {
    StubFollowsGetter followsInterface;
    StubParentGetter parentInterface;
    StubStmtGetter stmtInterface;
    StubConstProcVarGetter constProcVarInterface;

    std::unordered_map<int, std::string> readMap = {{1, "x"}};
    std::unordered_map<int, std::string> printMap = {{3, "z"}};
    std::unordered_set<int> assignStmtMap = {2, 4, 6, 8, 9, 10};
    std::unordered_set<int> ifStmtMap = {5};
    std::unordered_set<int> whileStmtMap = {7};
    std::unordered_set<std::string> varSet = {"a", "b", "c", "d", "e", "f", "g", "o", "w", "x", "y", "z"};
    std::unordered_set<std::string> procSet = {"fred", "ryan"};
    std::unordered_map<int, int> followsMap = {{1, 2},
                                               {2, 3},
                                               {4, 5},
                                               {5, 10},
                                               {7, 9}};
    std::unordered_map<int, std::unordered_set<int>> followsTMap = {{1, {2, 3}},
                                                                    {2, {3}},
                                                                    {4, {5, 10}},
                                                                    {5, {10}},
                                                                    {7, {9}}};
    std::unordered_map<int, std::unordered_set<int>> parentMapSet = {{5, {6, 7, 9}},
                                                                     {7, {8}}};
    std::unordered_map<int, std::unordered_set<int>> parentTMapSet = {{5, {6, 7, 8, 9}},
                                                                      {7, {8}}};


    // for expected results
    std::unordered_set<int> stmtSet = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    void initializeInterfaces() {
        followsInterface.setFollowsEntries(followsMap);
        followsInterface.setFollowsTEntries(followsTMap);
        parentInterface.setParentEntries(parentMapSet);
        parentInterface.setParentTEntries(parentTMapSet);
        constProcVarInterface.setVarEntries(varSet);
        constProcVarInterface.setProcEntries(procSet);
        stmtInterface.setReadStmtEntries(readMap);
        stmtInterface.setPrintStmtEntries(printMap);
        stmtInterface.setAssignStmtEntries(assignStmtMap);
        stmtInterface.setIfStmtEntries(ifStmtMap);
        stmtInterface.setWhileStmtEntries(whileStmtMap);
    }
}

using namespace test_parentfollows_eval;
using namespace query_func;

// stmt s, s1; assign a, a1; while w; if ifs; variable v, v1; 
// procedure p, p1; constant c; read re; print pn; call cl;

TEST_CASE("Evaluate Single Select - Single Follows") {
    initializeInterfaces();
    SECTION("Left Input") {
        SECTION("Follows(1, s) - Output") {
            std::unordered_set<std::string> expectedResult = {"2"};
            std::vector<std::shared_ptr<Clause>> clauseList;

            std::shared_ptr<EntityArgument> selection = std::make_shared<StmtStmtEntity>(&stmtInterface, "s", "");
            std::shared_ptr<Argument> firstArg = std::make_shared<IntInput>("1");
            std::shared_ptr<Argument> secondArg = std::make_shared<StmtStmtEntity>(&stmtInterface, "s", "");

            clauseList.push_back(std::make_shared<Clause>(std::make_shared<FollowsStrategy>(&followsInterface), firstArg, secondArg));

            TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
        }

        SECTION("Follows(3, s) - Empty") {
            std::unordered_set<std::string> expectedResult;
            std::vector<std::shared_ptr<Clause>> clauseList;

            std::shared_ptr<EntityArgument> selection = std::make_shared<StmtStmtEntity>(&stmtInterface, "s", "");
            std::shared_ptr<Argument> firstArg = std::make_shared<IntInput>("3");
            std::shared_ptr<Argument> secondArg = std::make_shared<StmtStmtEntity>(&stmtInterface, "s", "");

            clauseList.push_back(std::make_shared<Clause>(std::make_shared<FollowsStrategy>(&followsInterface), firstArg, secondArg));

            TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
        }

        SECTION("Follows*(4, s) - Output") {
            std::unordered_set<std::string> expectedResult = {"5", "10"};
            std::vector<std::shared_ptr<Clause>> clauseList;

            std::shared_ptr<EntityArgument> selection = std::make_shared<StmtStmtEntity>(&stmtInterface, "s", "");
            std::shared_ptr<Argument> firstArg = std::make_shared<IntInput>("4");
            std::shared_ptr<Argument> secondArg = std::make_shared<StmtStmtEntity>(&stmtInterface, "s", "");

            clauseList.push_back(std::make_shared<Clause>(std::make_shared<FollowsStrategy>(&followsInterface, true), firstArg, secondArg));

            TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
        }

        SECTION("Follows*(3, s) - Empty") {
            std::unordered_set<std::string> expectedResult;
            std::vector<std::shared_ptr<Clause>> clauseList;

            std::shared_ptr<EntityArgument> selection = std::make_shared<StmtStmtEntity>(&stmtInterface, "s", "");
            std::shared_ptr<Argument> firstArg = std::make_shared<IntInput>("3");
            std::shared_ptr<Argument> secondArg = std::make_shared<StmtStmtEntity>(&stmtInterface, "s", "");

            clauseList.push_back(std::make_shared<Clause>(std::make_shared<FollowsStrategy>(&followsInterface, true), firstArg, secondArg));

            TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
        }
    }

    SECTION("Right Input") {
        SECTION("Follows(s, 2) - Output") {
            std::unordered_set<std::string> expectedResult = {"1"};
            std::vector<std::shared_ptr<Clause>> clauseList;

            std::shared_ptr<EntityArgument> selection = std::make_shared<StmtStmtEntity>(&stmtInterface, "s", "");
            std::shared_ptr<Argument> firstArg = std::make_shared<StmtStmtEntity>(&stmtInterface, "s", "");
            std::shared_ptr<Argument> secondArg = std::make_shared<IntInput>("2");

            clauseList.push_back(std::make_shared<Clause>(std::make_shared<FollowsStrategy>(&followsInterface), firstArg, secondArg));

            TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
        }

        SECTION("Follows(s, 1) - Empty") {
            std::unordered_set<std::string> expectedResult;
            std::vector<std::shared_ptr<Clause>> clauseList;

            std::shared_ptr<EntityArgument> selection = std::make_shared<StmtStmtEntity>(&stmtInterface, "s", "");
            std::shared_ptr<Argument> firstArg = std::make_shared<StmtStmtEntity>(&stmtInterface, "s", "");
            std::shared_ptr<Argument> secondArg = std::make_shared<IntInput>("1");

            clauseList.push_back(std::make_shared<Clause>(std::make_shared<FollowsStrategy>(&followsInterface), firstArg, secondArg));

            TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
        }

        SECTION("Follows*(s, 10) - Output") {
            std::unordered_set<std::string> expectedResult = {"4", "5"};
            std::vector<std::shared_ptr<Clause>> clauseList;

            std::shared_ptr<EntityArgument> selection = std::make_shared<StmtStmtEntity>(&stmtInterface, "s", "");
            std::shared_ptr<Argument> firstArg = std::make_shared<StmtStmtEntity>(&stmtInterface, "s", "");
            std::shared_ptr<Argument> secondArg = std::make_shared<IntInput>("10");

            clauseList.push_back(std::make_shared<Clause>(std::make_shared<FollowsStrategy>(&followsInterface, true), firstArg, secondArg));

            TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
        }

        SECTION("Follows*(s, 4) - Empty") {
            std::unordered_set<std::string> expectedResult;
            std::vector<std::shared_ptr<Clause>> clauseList;

            std::shared_ptr<EntityArgument> selection = std::make_shared<StmtStmtEntity>(&stmtInterface, "s", "");
            std::shared_ptr<Argument> firstArg = std::make_shared<StmtStmtEntity>(&stmtInterface, "s", "");
            std::shared_ptr<Argument> secondArg = std::make_shared<IntInput>("4");

            clauseList.push_back(std::make_shared<Clause>(std::make_shared<FollowsStrategy>(&followsInterface, true), firstArg, secondArg));

            TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
        }
    }

    SECTION("Both Input") {

        SECTION("Follows(2, 3)") {
            SECTION("Select s - Output") {
                std::unordered_set<std::string> expectedResult = ConversionUtils::convertIntToStringSet(stmtSet);
                std::vector<std::shared_ptr<Clause>> clauseList;

                std::shared_ptr<EntityArgument> selection = std::make_shared<StmtStmtEntity>(&stmtInterface, "s", "");
                std::shared_ptr<Argument> firstArg = std::make_shared<IntInput>("2");
                std::shared_ptr<Argument> secondArg = std::make_shared<IntInput>("3");

                clauseList.push_back(std::make_shared<Clause>(std::make_shared<FollowsStrategy>(&followsInterface), firstArg, secondArg));

                TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
            }
        }

        SECTION("Follows*(2, 3)") {
            SECTION("Select s - Output") {
                std::unordered_set<std::string> expectedResult = ConversionUtils::convertIntToStringSet(stmtSet);
                std::vector<std::shared_ptr<Clause>> clauseList;

                std::shared_ptr<EntityArgument> selection = std::make_shared<StmtStmtEntity>(&stmtInterface, "s", "");
                std::shared_ptr<Argument> firstArg = std::make_shared<IntInput>("2");
                std::shared_ptr<Argument> secondArg = std::make_shared<IntInput>("3");

                clauseList.push_back(std::make_shared<Clause>(std::make_shared<FollowsStrategy>(&followsInterface, true), firstArg, secondArg));

                TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
            }
        }

        SECTION("Follows(4, 10)") {
            SECTION("Select s - Empty") {
                std::unordered_set<std::string> expectedResult;
                std::vector<std::shared_ptr<Clause>> clauseList;

                std::shared_ptr<EntityArgument> selection = std::make_shared<StmtStmtEntity>(&stmtInterface, "s", "");
                std::shared_ptr<Argument> firstArg = std::make_shared<IntInput>("4");
                std::shared_ptr<Argument> secondArg = std::make_shared<IntInput>("10");

                clauseList.push_back(std::make_shared<Clause>(std::make_shared<FollowsStrategy>(&followsInterface), firstArg, secondArg));

                TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
            }
        }

        SECTION("Follows*(4, 10)") {
            SECTION("Select s - Output") {
                std::unordered_set<std::string> expectedResult = ConversionUtils::convertIntToStringSet(stmtSet);
                std::vector<std::shared_ptr<Clause>> clauseList;

                std::shared_ptr<EntityArgument> selection = std::make_shared<StmtStmtEntity>(&stmtInterface, "s", "");
                std::shared_ptr<Argument> firstArg = std::make_shared<IntInput>("4");
                std::shared_ptr<Argument> secondArg = std::make_shared<IntInput>("10");

                clauseList.push_back(std::make_shared<Clause>(std::make_shared<FollowsStrategy>(&followsInterface, true), firstArg, secondArg));

                TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
            }
        }

        SECTION("Follows*(4, 6)") {
            SECTION("Select s - Empty") {
                std::unordered_set<std::string> expectedResult;
                std::vector<std::shared_ptr<Clause>> clauseList;

                std::shared_ptr<EntityArgument> selection = std::make_shared<StmtStmtEntity>(&stmtInterface, "s", "");
                std::shared_ptr<Argument> firstArg = std::make_shared<IntInput>("4");
                std::shared_ptr<Argument> secondArg = std::make_shared<IntInput>("6");

                clauseList.push_back(std::make_shared<Clause>(std::make_shared<FollowsStrategy>(&followsInterface, true), firstArg, secondArg));

                TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
            }
        }
    }

    SECTION("No Input") {
        SECTION("Follows(s, s1)") {
            SECTION("Select s - Output") {
                std::unordered_set<std::string> expectedResult = {"1", "2", "4", "5", "7"};
                std::vector<std::shared_ptr<Clause>> clauseList;

                std::shared_ptr<EntityArgument> selection = std::make_shared<StmtStmtEntity>(&stmtInterface, "s", "");
                std::shared_ptr<Argument> firstArg = std::make_shared<StmtStmtEntity>(&stmtInterface, "s", "");
                std::shared_ptr<Argument> secondArg = std::make_shared<StmtStmtEntity>(&stmtInterface, "s1", "");

                clauseList.push_back(std::make_shared<Clause>(std::make_shared<FollowsStrategy>(&followsInterface), firstArg, secondArg));

                TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
            }

            SECTION("Select s1 - Output") {
                std::unordered_set<std::string> expectedResult = {"2", "3", "5", "9", "10"};
                std::vector<std::shared_ptr<Clause>> clauseList;

                std::shared_ptr<EntityArgument> selection = std::make_shared<StmtStmtEntity>(&stmtInterface, "s1", "");
                std::shared_ptr<Argument> firstArg = std::make_shared<StmtStmtEntity>(&stmtInterface, "s", "");
                std::shared_ptr<Argument> secondArg = std::make_shared<StmtStmtEntity>(&stmtInterface, "s1", "");

                clauseList.push_back(std::make_shared<Clause>(std::make_shared<FollowsStrategy>(&followsInterface), firstArg, secondArg));

                TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
            }
        }

        SECTION("Follows*(s, s1)") {
            SECTION("Select s - Output") {
                std::unordered_set<std::string> expectedResult = {"1", "2", "4", "5", "7"};
                std::vector<std::shared_ptr<Clause>> clauseList;

                std::shared_ptr<EntityArgument> selection = std::make_shared<StmtStmtEntity>(&stmtInterface, "s", "");
                std::shared_ptr<Argument> firstArg = std::make_shared<StmtStmtEntity>(&stmtInterface, "s", "");
                std::shared_ptr<Argument> secondArg = std::make_shared<StmtStmtEntity>(&stmtInterface, "s1", "");

                clauseList.push_back(std::make_shared<Clause>(std::make_shared<FollowsStrategy>(&followsInterface, true), firstArg, secondArg));

                TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
            }

            SECTION("Select s1 - Output") {
                std::unordered_set<std::string> expectedResult = {"2", "3", "5", "9", "10"};
                std::vector<std::shared_ptr<Clause>> clauseList;

                std::shared_ptr<EntityArgument> selection = std::make_shared<StmtStmtEntity>(&stmtInterface, "s1", "");
                std::shared_ptr<Argument> firstArg = std::make_shared<StmtStmtEntity>(&stmtInterface, "s", "");
                std::shared_ptr<Argument> secondArg = std::make_shared<StmtStmtEntity>(&stmtInterface, "s1", "");

                clauseList.push_back(std::make_shared<Clause>(std::make_shared<FollowsStrategy>(&followsInterface, true), firstArg, secondArg));

                TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
            }
        }
    }
}

TEST_CASE("Evaluate Single Select - Single Parent") {
    initializeInterfaces();

    SECTION("Left Input") {
        SECTION("Parent(5, s) - Output") {
            std::unordered_set<std::string> expectedResult = {"6", "7", "9"};
            std::vector<std::shared_ptr<Clause>> clauseList;

            std::shared_ptr<EntityArgument> selection = std::make_shared<StmtStmtEntity>(&stmtInterface, "s", "");
            std::shared_ptr<Argument> firstArg = std::make_shared<IntInput>("5");
            std::shared_ptr<Argument> secondArg = std::make_shared<StmtStmtEntity>(&stmtInterface, "s", "");

            clauseList.push_back(std::make_shared<Clause>(std::make_shared<ParentStrategy>(&parentInterface), firstArg, secondArg));

            TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
        }

        SECTION("Parent(1, s) - Empty") {
            std::unordered_set<std::string> expectedResult;
            std::vector<std::shared_ptr<Clause>> clauseList;

            std::shared_ptr<EntityArgument> selection = std::make_shared<StmtStmtEntity>(&stmtInterface, "s", "");
            std::shared_ptr<Argument> firstArg = std::make_shared<IntInput>("1");
            std::shared_ptr<Argument> secondArg = std::make_shared<StmtStmtEntity>(&stmtInterface, "s", "");

            clauseList.push_back(std::make_shared<Clause>(std::make_shared<ParentStrategy>(&parentInterface), firstArg, secondArg));

            TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
        }

        SECTION("Parent*(5, s) - Output") {
            std::unordered_set<std::string> expectedResult = {"6", "7", "8", "9"};
            std::vector<std::shared_ptr<Clause>> clauseList;

            std::shared_ptr<EntityArgument> selection = std::make_shared<StmtStmtEntity>(&stmtInterface, "s", "");
            std::shared_ptr<Argument> firstArg = std::make_shared<IntInput>("5");
            std::shared_ptr<Argument> secondArg = std::make_shared<StmtStmtEntity>(&stmtInterface, "s", "");

            clauseList.push_back(std::make_shared<Clause>(std::make_shared<ParentStrategy>(&parentInterface, true), firstArg, secondArg));

            TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
        }

        SECTION("Parent*(1, s) - Empty") {
            std::unordered_set<std::string> expectedResult;
            std::vector<std::shared_ptr<Clause>> clauseList;

            std::shared_ptr<EntityArgument> selection = std::make_shared<StmtStmtEntity>(&stmtInterface, "s", "");
            std::shared_ptr<Argument> firstArg = std::make_shared<IntInput>("1");
            std::shared_ptr<Argument> secondArg = std::make_shared<StmtStmtEntity>(&stmtInterface, "s", "");

            clauseList.push_back(std::make_shared<Clause>(std::make_shared<ParentStrategy>(&parentInterface, true), firstArg, secondArg));

            TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
        }
    }

    SECTION("Right Input") {
        SECTION("Parent(s, 7) - Output") {
            std::unordered_set<std::string> expectedResult = {"5"};
            std::vector<std::shared_ptr<Clause>> clauseList;

            std::shared_ptr<EntityArgument> selection = std::make_shared<StmtStmtEntity>(&stmtInterface, "s", "");
            std::shared_ptr<Argument> firstArg = std::make_shared<StmtStmtEntity>(&stmtInterface, "s", "");
            std::shared_ptr<Argument> secondArg = std::make_shared<IntInput>("7");

            clauseList.push_back(std::make_shared<Clause>(std::make_shared<ParentStrategy>(&parentInterface), firstArg, secondArg));

            TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
        }

        SECTION("Parent(s, 5) - Empty") {
            std::unordered_set<std::string> expectedResult;
            std::vector<std::shared_ptr<Clause>> clauseList;

            std::shared_ptr<EntityArgument> selection = std::make_shared<StmtStmtEntity>(&stmtInterface, "s", "");
            std::shared_ptr<Argument> firstArg = std::make_shared<StmtStmtEntity>(&stmtInterface, "s", "");
            std::shared_ptr<Argument> secondArg = std::make_shared<IntInput>("5");

            clauseList.push_back(std::make_shared<Clause>(std::make_shared<ParentStrategy>(&parentInterface), firstArg, secondArg));

            TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
        }

        SECTION("Parent*(s, 8) - Output") {
            std::unordered_set<std::string> expectedResult = {"5", "7"};
            std::vector<std::shared_ptr<Clause>> clauseList;

            std::shared_ptr<EntityArgument> selection = std::make_shared<StmtStmtEntity>(&stmtInterface, "s", "");
            std::shared_ptr<Argument> firstArg = std::make_shared<StmtStmtEntity>(&stmtInterface, "s", "");
            std::shared_ptr<Argument> secondArg = std::make_shared<IntInput>("8");

            clauseList.push_back(std::make_shared<Clause>(std::make_shared<ParentStrategy>(&parentInterface, true), firstArg, secondArg));

            TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
        }

        SECTION("Parent*(s, 5) - Empty") {
            std::unordered_set<std::string> expectedResult;
            std::vector<std::shared_ptr<Clause>> clauseList;

            std::shared_ptr<EntityArgument> selection = std::make_shared<StmtStmtEntity>(&stmtInterface, "s", "");
            std::shared_ptr<Argument> firstArg = std::make_shared<StmtStmtEntity>(&stmtInterface, "s", "");
            std::shared_ptr<Argument> secondArg = std::make_shared<IntInput>("5");

            clauseList.push_back(std::make_shared<Clause>(std::make_shared<ParentStrategy>(&parentInterface, true), firstArg, secondArg));

            TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
        }
    }

    SECTION("Both Input") {
        std::unordered_set<std::string> expectedResult = ConversionUtils::convertIntToStringSet(stmtSet);

        SECTION("Parent(5, 7)") {
            SECTION("Select s - Output") {
                std::unordered_set<std::string> expectedResult = ConversionUtils::convertIntToStringSet(stmtSet);
                std::vector<std::shared_ptr<Clause>> clauseList;

                std::shared_ptr<EntityArgument> selection = std::make_shared<StmtStmtEntity>(&stmtInterface, "s", "");
                std::shared_ptr<Argument> firstArg = std::make_shared<IntInput>("5");
                std::shared_ptr<Argument> secondArg = std::make_shared<IntInput>("7");

                clauseList.push_back(std::make_shared<Clause>(std::make_shared<ParentStrategy>(&parentInterface), firstArg, secondArg));

                TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
            }
        }

        SECTION("Parent*(5, 7)") {
            SECTION("Select s - Output") {
                std::unordered_set<std::string> expectedResult = ConversionUtils::convertIntToStringSet(stmtSet);
                std::vector<std::shared_ptr<Clause>> clauseList;

                std::shared_ptr<EntityArgument> selection = std::make_shared<StmtStmtEntity>(&stmtInterface, "s", "");
                std::shared_ptr<Argument> firstArg = std::make_shared<IntInput>("5");
                std::shared_ptr<Argument> secondArg = std::make_shared<IntInput>("7");

                clauseList.push_back(std::make_shared<Clause>(std::make_shared<ParentStrategy>(&parentInterface, true), firstArg, secondArg));

                TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
            }
        }

        SECTION("Parent(5, 8)") {
            SECTION("Select s - Empty") {
                std::unordered_set<std::string> expectedResult;
                std::vector<std::shared_ptr<Clause>> clauseList;

                std::shared_ptr<EntityArgument> selection = std::make_shared<StmtStmtEntity>(&stmtInterface, "s", "");
                std::shared_ptr<Argument> firstArg = std::make_shared<IntInput>("5");
                std::shared_ptr<Argument> secondArg = std::make_shared<IntInput>("8");

                clauseList.push_back(std::make_shared<Clause>(std::make_shared<ParentStrategy>(&parentInterface), firstArg, secondArg));

                TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
            }
        }

        SECTION("Parent*(5, 8)") {
            SECTION("Select s - Output") {
                std::unordered_set<std::string> expectedResult = ConversionUtils::convertIntToStringSet(stmtSet);
                std::vector<std::shared_ptr<Clause>> clauseList;

                std::shared_ptr<EntityArgument> selection = std::make_shared<StmtStmtEntity>(&stmtInterface, "s", "");
                std::shared_ptr<Argument> firstArg = std::make_shared<IntInput>("5");
                std::shared_ptr<Argument> secondArg = std::make_shared<IntInput>("8");

                clauseList.push_back(std::make_shared<Clause>(std::make_shared<ParentStrategy>(&parentInterface, true), firstArg, secondArg));

                TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
            }
        }

        SECTION("Parent*(1, 6)") {
            SECTION("Select s - Empty") {
                std::unordered_set<std::string> expectedResult;
                std::vector<std::shared_ptr<Clause>> clauseList;

                std::shared_ptr<EntityArgument> selection = std::make_shared<StmtStmtEntity>(&stmtInterface, "s", "");
                std::shared_ptr<Argument> firstArg = std::make_shared<IntInput>("1");
                std::shared_ptr<Argument> secondArg = std::make_shared<IntInput>("6");

                clauseList.push_back(std::make_shared<Clause>(std::make_shared<ParentStrategy>(&parentInterface, true), firstArg, secondArg));

                TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
            }
        }
    }

    SECTION("No Input") {
        SECTION("Parent(s, s1)") {
            SECTION("Select s - Output") {
                std::unordered_set<std::string> expectedResult = {"5", "7"};
                std::vector<std::shared_ptr<Clause>> clauseList;

                std::shared_ptr<EntityArgument> selection = std::make_shared<StmtStmtEntity>(&stmtInterface, "s", "");
                std::shared_ptr<Argument> firstArg = std::make_shared<StmtStmtEntity>(&stmtInterface, "s", "");
                std::shared_ptr<Argument> secondArg = std::make_shared<StmtStmtEntity>(&stmtInterface, "s1", "");

                clauseList.push_back(std::make_shared<Clause>(std::make_shared<ParentStrategy>(&parentInterface), firstArg, secondArg));

                TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
            }

            SECTION("Select s1 - Output") {
                std::unordered_set<std::string> expectedResult = {"6", "7", "8", "9"};
                std::vector<std::shared_ptr<Clause>> clauseList;

                std::shared_ptr<EntityArgument> selection = std::make_shared<StmtStmtEntity>(&stmtInterface, "s1", "");
                std::shared_ptr<Argument> firstArg = std::make_shared<StmtStmtEntity>(&stmtInterface, "s", "");
                std::shared_ptr<Argument> secondArg = std::make_shared<StmtStmtEntity>(&stmtInterface, "s1", "");

                clauseList.push_back(std::make_shared<Clause>(std::make_shared<ParentStrategy>(&parentInterface), firstArg, secondArg));

                TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
            }
        }

        SECTION("Parent*(s, s1)") {
            SECTION("Select s - Output") {
                std::unordered_set<std::string> expectedResult = {"5", "7"};
                std::vector<std::shared_ptr<Clause>> clauseList;

                std::shared_ptr<EntityArgument> selection = std::make_shared<StmtStmtEntity>(&stmtInterface, "s", "");
                std::shared_ptr<Argument> firstArg = std::make_shared<StmtStmtEntity>(&stmtInterface, "s", "");
                std::shared_ptr<Argument> secondArg = std::make_shared<StmtStmtEntity>(&stmtInterface, "s1", "");

                clauseList.push_back(std::make_shared<Clause>(std::make_shared<ParentStrategy>(&parentInterface, true), firstArg, secondArg));

                TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
            }

            SECTION("Select s1 - Output") {
                std::unordered_set<std::string> expectedResult = {"6", "7", "8", "9"};
                std::vector<std::shared_ptr<Clause>> clauseList;

                std::shared_ptr<EntityArgument> selection = std::make_shared<StmtStmtEntity>(&stmtInterface, "s1", "");
                std::shared_ptr<Argument> firstArg = std::make_shared<StmtStmtEntity>(&stmtInterface, "s", "");
                std::shared_ptr<Argument> secondArg = std::make_shared<StmtStmtEntity>(&stmtInterface, "s1", "");

                clauseList.push_back(std::make_shared<Clause>(std::make_shared<ParentStrategy>(&parentInterface, true), firstArg, secondArg));

                TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
            }
        }
    }
}
