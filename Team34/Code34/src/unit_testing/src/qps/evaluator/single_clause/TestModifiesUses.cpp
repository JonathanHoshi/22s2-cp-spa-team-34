#include <memory>
#include <unordered_set>
#include <unordered_map>

#include "catch.hpp"
#include "qps/argument/entity/VariableEntity.h"
#include "qps/argument/entity/ProcedureEntity.h"
#include "qps/argument/entity/stmt/ReadStmtEntity.h"
#include "qps/argument/entity/stmt/StmtStmtEntity.h"
#include "qps/argument/input/IntInput.h"
#include "qps/argument/input/StringInput.h"
#include "qps/clause/strategy/relation/ModifiesStrategy.h"
#include "qps/clause/strategy/relation/UsesStrategy.h"
#include "../stub_entity/StubConstProcVarGetter.cpp"
#include "../stub_entity/StubStmtGetter.cpp"
#include "../stub_clause/StubModifiesGetter.cpp"
#include "../stub_clause/StubUsesGetter.cpp"
#include "../QueryFunction.h"

namespace test_modifiesuses_eval {

    StubModifiesGetter modifiesInterface;
    StubUsesGetter usesInterface;
    StubStmtGetter stmtInterface;
    StubConstProcVarGetter constProcVarInterface;

    std::unordered_map<int, std::string> readMap = {{1, "x"},
        {4, "x"},
        {11, "d"}};
    std::unordered_map<int, std::string> printMap = {{3, "z"},
        {16, "k"}};
    std::unordered_map<int, std::string> callStmtMap = {{13, "cx"}};
    std::unordered_set<int> assignStmtSet = {2, 5, 6, 8, 10, 14, 15};
    std::unordered_set<int> ifStmtMap = {7};
    std::unordered_set<int> whileStmtMap = {9, 12};
    std::unordered_set<std::string> varSet = {"a", "b", "c", "d", "e", "f", "i", "k", "l", "p", "v", "w", "x", "y", "z"};
    std::unordered_set<std::string> procSet = {"cx", "fred", "jon", "nat", "ryan"};
    std::unordered_map<std::string, std::unordered_set<std::string>> modifiesPMapSet = {{"cx", {"f", "p"}},
        {"fred", {"x", "y"}},
        {"jon", {"d", "f", "p"}},
        {"nat", {"x", "z"}},
        {"ryan", {"a", "x", "y"}}};
    std::unordered_map<int, std::unordered_set<std::string>> modifiesSMapSet = {{1, {"x"}},
        {2, {"y"}},
        {4, {"x"}},
        {5, {"z"}},
        {6, {"x"}},
        {7, {"a", "y"}},
        {8, {"y"}},
        {9, {"a"}},
        {10, {"a"}},
        {11, {"d"}},
        {12, {"f", "p"}},
        {13, {"f", "p"}},
        {14, {"p"}},
        {15, {"f"}}};
    std::unordered_map<std::string, std::unordered_set<std::string>> usesPMapSet = {{"cx", {"a", "f", "i", "k", "l", "v", "x", "y"}},
        {"fred", {"z"}},
        {"jon", {"a", "e", "f", "i", "k", "l", "v", "x", "y"}},
        {"ryan", {"a", "b", "c", "w", "x"}}};
    std::unordered_map<int, std::unordered_set<std::string>> usesSMapSet = {{3, {"z"}},
        {7, {"a", "b", "c", "w", "x"}},
        {8, {"x"}},
        {9, {"a", "b", "c"}},
        {10, {"a"}},
        {12, {"a", "e", "f", "i", "k", "l", "v", "x", "y"}},
        {13, {"a", "f", "i", "k", "l", "v", "x", "y"}}};

    void initializeInterfaces() {
        modifiesInterface.setModifiesPEntries(modifiesPMapSet);
        modifiesInterface.setModifiesSEntries(modifiesSMapSet);
        usesInterface.setUsesPEntries(usesPMapSet);
        usesInterface.setUsesSEntries(usesSMapSet);
        constProcVarInterface.setVarEntries(varSet);
        constProcVarInterface.setProcEntries(procSet);
        stmtInterface.setReadStmtEntries(readMap);
        stmtInterface.setPrintStmtEntries(printMap);
        stmtInterface.setCallStmtEntries(callStmtMap);
        stmtInterface.setAssignStmtEntries(assignStmtSet);
        stmtInterface.setIfStmtEntries(ifStmtMap);
        stmtInterface.setWhileStmtEntries(whileStmtMap);
    }
}

using namespace test_modifiesuses_eval;
using namespace query_func;

// stmt s, s1; assign a, a1; while w; if ifs; variable v, v1; 
// procedure p, p1; constant c; read re; print pn; call cl;

TEST_CASE("Evaluate Single Select - Single ModifiesP") {
    initializeInterfaces();
    SECTION("Left Input") {
        SECTION("Modifies('fred', v) - Output") {
            std::unordered_set<std::string> expectedResult = {"x", "y"};
            std::vector<std::shared_ptr<Clause>> clauseList;

            std::shared_ptr<EntityArgument> selection = std::make_shared<VariableEntity>(&constProcVarInterface, "v", "");
            std::shared_ptr<Argument> firstArg = std::make_shared<StringInput>("fred");
            std::shared_ptr<Argument> secondArg = std::make_shared<VariableEntity>(&constProcVarInterface, "v", "");

            clauseList.push_back(std::make_shared<Clause>(std::make_shared<ModifiesStrategy>(&modifiesInterface, true), firstArg, secondArg));

            TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
        }

        SECTION("Modifies('jon', v) - Output") {
            std::unordered_set<std::string> expectedResult = {"d", "f", "p"};
            std::vector<std::shared_ptr<Clause>> clauseList;

            std::shared_ptr<EntityArgument> selection = std::make_shared<VariableEntity>(&constProcVarInterface, "v", "");
            std::shared_ptr<Argument> firstArg = std::make_shared<StringInput>("jon");
            std::shared_ptr<Argument> secondArg = std::make_shared<VariableEntity>(&constProcVarInterface, "v", "");

            clauseList.push_back(std::make_shared<Clause>(std::make_shared<ModifiesStrategy>(&modifiesInterface, true), firstArg, secondArg));

            TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
        }
    }

    SECTION("Right Input") {
        SECTION("Modifies(p, 'y') - Output") {
            std::unordered_set<std::string> expectedResult = {"fred", "ryan"};
            std::vector<std::shared_ptr<Clause>> clauseList;

            std::shared_ptr<EntityArgument> selection = std::make_shared<ProcedureEntity>(&constProcVarInterface, "p", "");
            std::shared_ptr<Argument> firstArg = std::make_shared<ProcedureEntity>(&constProcVarInterface, "p", "");
            std::shared_ptr<Argument> secondArg = std::make_shared<StringInput>("y");

            clauseList.push_back(std::make_shared<Clause>(std::make_shared<ModifiesStrategy>(&modifiesInterface, true), firstArg, secondArg));

            TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
        }

        SECTION("Modifies(p, 'g') - Empty") {
            std::unordered_set<std::string> expectedResult;
            std::vector<std::shared_ptr<Clause>> clauseList;

            std::shared_ptr<EntityArgument> selection = std::make_shared<ProcedureEntity>(&constProcVarInterface, "p", "");
            std::shared_ptr<Argument> firstArg = std::make_shared<ProcedureEntity>(&constProcVarInterface, "p", "");
            std::shared_ptr<Argument> secondArg = std::make_shared<StringInput>("g");

            clauseList.push_back(std::make_shared<Clause>(std::make_shared<ModifiesStrategy>(&modifiesInterface, true), firstArg, secondArg));

            TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
        }

        SECTION("Modifies(p, _) - Output") {
            std::unordered_set<std::string> expectedResult = {"cx", "fred", "jon", "nat", "ryan"};
            std::vector<std::shared_ptr<Clause>> clauseList;

            std::shared_ptr<EntityArgument> selection = std::make_shared<ProcedureEntity>(&constProcVarInterface, "p", "");
            std::shared_ptr<Argument> firstArg = std::make_shared<ProcedureEntity>(&constProcVarInterface, "p", "");

            std::shared_ptr<WildcardEntity> wcEntity = std::make_shared<WildcardEntity>();
            wcEntity->assignEntityType(std::make_shared<VariableEntity>(&constProcVarInterface, "", ""));
            std::shared_ptr<Argument> secondArg = wcEntity;

            clauseList.push_back(std::make_shared<Clause>(std::make_shared<ModifiesStrategy>(&modifiesInterface, true), firstArg, secondArg));

            TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
        }
    }

    SECTION("Both Input") {
        SECTION("Modifies('fred', 'y')") {
            SECTION("Select v - Output") {
                std::unordered_set<std::string> expectedResult = varSet;
                std::vector<std::shared_ptr<Clause>> clauseList;

                std::shared_ptr<EntityArgument> selection = std::make_shared<VariableEntity>(&constProcVarInterface, "v", "");
                std::shared_ptr<Argument> firstArg = std::make_shared<StringInput>("fred");
                std::shared_ptr<Argument> secondArg = std::make_shared<StringInput>("y");

                clauseList.push_back(std::make_shared<Clause>(std::make_shared<ModifiesStrategy>(&modifiesInterface, true), firstArg, secondArg));

                TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
            }
        }

        SECTION("Modifies('fred', 'z')") {
            SECTION("Select v - Empty") {
                std::unordered_set<std::string> expectedResult;
                std::vector<std::shared_ptr<Clause>> clauseList;

                std::shared_ptr<EntityArgument> selection = std::make_shared<VariableEntity>(&constProcVarInterface, "v", "");
                std::shared_ptr<Argument> firstArg = std::make_shared<StringInput>("fred");
                std::shared_ptr<Argument> secondArg = std::make_shared<StringInput>("z");

                clauseList.push_back(std::make_shared<Clause>(std::make_shared<ModifiesStrategy>(&modifiesInterface, true), firstArg, secondArg));

                TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
            }
        }
    }

    SECTION("No Input") {
        SECTION("Modifies(p, v)") {
            SECTION("Select p - Output") {
                std::unordered_set<std::string> expectedResult = procSet;
                std::vector<std::shared_ptr<Clause>> clauseList;

                std::shared_ptr<EntityArgument> selection = std::make_shared<ProcedureEntity>(&constProcVarInterface, "p", "");
                std::shared_ptr<Argument> firstArg = std::make_shared<ProcedureEntity>(&constProcVarInterface, "p", "");
                std::shared_ptr<Argument> secondArg = std::make_shared<VariableEntity>(&constProcVarInterface, "v", "");

                clauseList.push_back(std::make_shared<Clause>(std::make_shared<ModifiesStrategy>(&modifiesInterface, true), firstArg, secondArg));

                TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
            }

            SECTION("Select v - Output") {
                std::unordered_set<std::string> expectedResult = {"a", "d", "f", "p", "x", "y", "z"};
                std::vector<std::shared_ptr<Clause>> clauseList;

                std::shared_ptr<EntityArgument> selection = std::make_shared<VariableEntity>(&constProcVarInterface, "v", "");
                std::shared_ptr<Argument> firstArg = std::make_shared<ProcedureEntity>(&constProcVarInterface, "p", "");
                std::shared_ptr<Argument> secondArg = std::make_shared<VariableEntity>(&constProcVarInterface, "v", "");

                clauseList.push_back(std::make_shared<Clause>(std::make_shared<ModifiesStrategy>(&modifiesInterface, true), firstArg, secondArg));

                TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
            }
        }
    }
}

TEST_CASE("Evaluate Single Select - Single ModifiesS") {
    initializeInterfaces();
    SECTION("Left Input") {
        SECTION("Modifies(1, v) - Output") {
            std::unordered_set<std::string> expectedResult = {"x"};
            std::vector<std::shared_ptr<Clause>> clauseList;

            std::shared_ptr<EntityArgument> selection = std::make_shared<VariableEntity>(&constProcVarInterface, "v", "");
            std::shared_ptr<Argument> firstArg = std::make_shared<IntInput>("1");
            std::shared_ptr<Argument> secondArg = std::make_shared<VariableEntity>(&constProcVarInterface, "v", "");

            clauseList.push_back(std::make_shared<Clause>(std::make_shared<ModifiesStrategy>(&modifiesInterface), firstArg, secondArg));

            TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
        }

        SECTION("Modifies(3, v) - Empty") {
            std::unordered_set<std::string> expectedResult;
            std::vector<std::shared_ptr<Clause>> clauseList;

            std::shared_ptr<EntityArgument> selection = std::make_shared<VariableEntity>(&constProcVarInterface, "v", "");
            std::shared_ptr<Argument> firstArg = std::make_shared<IntInput>("3");
            std::shared_ptr<Argument> secondArg = std::make_shared<VariableEntity>(&constProcVarInterface, "v", "");

            clauseList.push_back(std::make_shared<Clause>(std::make_shared<ModifiesStrategy>(&modifiesInterface), firstArg, secondArg));

            TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
        }
    }

    SECTION("Right Input") {
        SECTION("Modifies(r, 'x') - Output") {
            std::unordered_set<std::string> expectedResult = {"1", "4"};
            std::vector<std::shared_ptr<Clause>> clauseList;

            std::shared_ptr<EntityArgument> selection = std::make_shared<ReadStmtEntity>(&stmtInterface, "r", "");
            std::shared_ptr<Argument> firstArg = std::make_shared<ReadStmtEntity>(&stmtInterface, "r", "");
            std::shared_ptr<Argument> secondArg = std::make_shared<StringInput>("x");

            clauseList.push_back(std::make_shared<Clause>(std::make_shared<ModifiesStrategy>(&modifiesInterface), firstArg, secondArg));

            TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
        }

        SECTION("Modifies(r, 'y') - Empty") {
            std::unordered_set<std::string> expectedResult;
            std::vector<std::shared_ptr<Clause>> clauseList;

            std::shared_ptr<EntityArgument> selection = std::make_shared<ReadStmtEntity>(&stmtInterface, "r", "");
            std::shared_ptr<Argument> firstArg = std::make_shared<ReadStmtEntity>(&stmtInterface, "r", "");
            std::shared_ptr<Argument> secondArg = std::make_shared<StringInput>("y");

            clauseList.push_back(std::make_shared<Clause>(std::make_shared<ModifiesStrategy>(&modifiesInterface), firstArg, secondArg));

            TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
        }

        SECTION("Modifies(s, 'y') - Output") {
            std::unordered_set<std::string> expectedResult = {"2", "7", "8"};
            std::vector<std::shared_ptr<Clause>> clauseList;

            std::shared_ptr<EntityArgument> selection = std::make_shared<StmtStmtEntity>(&stmtInterface, "s", "");
            std::shared_ptr<Argument> firstArg = std::make_shared<StmtStmtEntity>(&stmtInterface, "s", "");
            std::shared_ptr<Argument> secondArg = std::make_shared<StringInput>("y");

            clauseList.push_back(std::make_shared<Clause>(std::make_shared<ModifiesStrategy>(&modifiesInterface), firstArg, secondArg));

            TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
        }
    }

    SECTION("Both Input") {
        SECTION("Modifies(1, 'x')") {
            SECTION("Select v - Output") {
                std::unordered_set<std::string> expectedResult = varSet;
                std::vector<std::shared_ptr<Clause>> clauseList;

                std::shared_ptr<EntityArgument> selection = std::make_shared<VariableEntity>(&constProcVarInterface, "v", "");
                std::shared_ptr<Argument> firstArg = std::make_shared<StringInput>("1");
                std::shared_ptr<Argument> secondArg = std::make_shared<StringInput>("x");

                clauseList.push_back(std::make_shared<Clause>(std::make_shared<ModifiesStrategy>(&modifiesInterface), firstArg, secondArg));

                TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
            }
        }

        SECTION("Modifies(1, 'w')") {
            SECTION("Select v - Empty") {
                std::unordered_set<std::string> expectedResult;
                std::vector<std::shared_ptr<Clause>> clauseList;

                std::shared_ptr<EntityArgument> selection = std::make_shared<VariableEntity>(&constProcVarInterface, "v", "");
                std::shared_ptr<Argument> firstArg = std::make_shared<StringInput>("1");
                std::shared_ptr<Argument> secondArg = std::make_shared<StringInput>("w");

                clauseList.push_back(std::make_shared<Clause>(std::make_shared<ModifiesStrategy>(&modifiesInterface), firstArg, secondArg));

                TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
            }
        }
    }

    SECTION("No Input") {
        SECTION("Modifies(r, v)") {
            SECTION("Select v - Output") {
                std::unordered_set<std::string> expectedResult = {"x", "d"};
                std::vector<std::shared_ptr<Clause>> clauseList;

                std::shared_ptr<EntityArgument> selection = std::make_shared<VariableEntity>(&constProcVarInterface, "v", "");
                std::shared_ptr<Argument> firstArg = std::make_shared<ReadStmtEntity>(&stmtInterface, "r", "");
                std::shared_ptr<Argument> secondArg = std::make_shared<VariableEntity>(&constProcVarInterface, "v", "");

                clauseList.push_back(std::make_shared<Clause>(std::make_shared<ModifiesStrategy>(&modifiesInterface), firstArg, secondArg));

                TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
            }

            SECTION("Select r - Output") {
                std::unordered_set<std::string> expectedResult = {"1", "4", "11"};
                std::vector<std::shared_ptr<Clause>> clauseList;

                std::shared_ptr<EntityArgument> selection = std::make_shared<ReadStmtEntity>(&stmtInterface, "r", "");
                std::shared_ptr<Argument> firstArg = std::make_shared<ReadStmtEntity>(&stmtInterface, "r", "");
                std::shared_ptr<Argument> secondArg = std::make_shared<VariableEntity>(&constProcVarInterface, "v", "");
                clauseList.push_back(std::make_shared<Clause>(std::make_shared<ModifiesStrategy>(&modifiesInterface), firstArg, secondArg));

                TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
            }
        }
    }

}

TEST_CASE("Evaluate Single Select - Single UsesP") {
    initializeInterfaces();
    SECTION("Left Input") {
        SECTION("Uses('fred', v) - Output") {
            std::unordered_set<std::string> expectedResult = {"z"};
            std::vector<std::shared_ptr<Clause>> clauseList;

            std::shared_ptr<EntityArgument> selection = std::make_shared<VariableEntity>(&constProcVarInterface, "v", "");
            std::shared_ptr<Argument> firstArg = std::make_shared<StringInput>("fred");
            std::shared_ptr<Argument> secondArg = std::make_shared<VariableEntity>(&constProcVarInterface, "v", "");

            clauseList.push_back(std::make_shared<Clause>(std::make_shared<UsesStrategy>(&usesInterface, true), firstArg, secondArg));

            TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
        }

        SECTION("Uses('nat', v) - Empty") {
            std::unordered_set<std::string> expectedResult;
            std::vector<std::shared_ptr<Clause>> clauseList;

            std::shared_ptr<EntityArgument> selection = std::make_shared<VariableEntity>(&constProcVarInterface, "v", "");
            std::shared_ptr<Argument> firstArg = std::make_shared<StringInput>("nat");
            std::shared_ptr<Argument> secondArg = std::make_shared<VariableEntity>(&constProcVarInterface, "v", "");

            clauseList.push_back(std::make_shared<Clause>(std::make_shared<UsesStrategy>(&usesInterface, true), firstArg, secondArg));

            TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
        }
    }

    SECTION("Right Input") {
        SECTION("Uses(p, 'w') - Output") {
            std::unordered_set<std::string> expectedResult = {"ryan"};
            std::vector<std::shared_ptr<Clause>> clauseList;

            std::shared_ptr<EntityArgument> selection = std::make_shared<ProcedureEntity>(&constProcVarInterface, "p", "");
            std::shared_ptr<Argument> firstArg = std::make_shared<ProcedureEntity>(&constProcVarInterface, "p", "");
            std::shared_ptr<Argument> secondArg = std::make_shared<StringInput>("w");

            clauseList.push_back(std::make_shared<Clause>(std::make_shared<UsesStrategy>(&usesInterface, true), firstArg, secondArg));

            TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
        }

        SECTION("Uses(p, _) - Output") {
            std::unordered_set<std::string> expectedResult = {"cx", "fred", "jon", "ryan"};
            std::vector<std::shared_ptr<Clause>> clauseList;

            std::shared_ptr<EntityArgument> selection = std::make_shared<ProcedureEntity>(&constProcVarInterface, "p", "");
            std::shared_ptr<Argument> firstArg = std::make_shared<ProcedureEntity>(&constProcVarInterface, "p", "");
            std::shared_ptr<WildcardEntity> wcEntity = std::make_shared<WildcardEntity>();
            wcEntity->assignEntityType(std::make_shared<VariableEntity>(&constProcVarInterface, "", ""));
            std::shared_ptr<Argument> secondArg = wcEntity;

            clauseList.push_back(std::make_shared<Clause>(std::make_shared<UsesStrategy>(&usesInterface, true), firstArg, secondArg));

            TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
        }
    }

    SECTION("Both Input") {
        SECTION("Uses('fred', 'z') - Output") {
            SECTION("Select p") {
                std::unordered_set<std::string> expectedResult = procSet;
                std::vector<std::shared_ptr<Clause>> clauseList;

                std::shared_ptr<EntityArgument> selection = std::make_shared<ProcedureEntity>(&constProcVarInterface, "p", "");
                std::shared_ptr<Argument> firstArg = std::make_shared<StringInput>("fred");
                std::shared_ptr<Argument> secondArg = std::make_shared<StringInput>("z");

                clauseList.push_back(std::make_shared<Clause>(std::make_shared<UsesStrategy>(&usesInterface, true), firstArg, secondArg));

                TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
            }
        }

        SECTION("Uses('fred', 'l') - Output") {
            SECTION("Select p") {
                std::unordered_set<std::string> expectedResult;
                std::vector<std::shared_ptr<Clause>> clauseList;

                std::shared_ptr<EntityArgument> selection = std::make_shared<ProcedureEntity>(&constProcVarInterface, "p", "");
                std::shared_ptr<Argument> firstArg = std::make_shared<StringInput>("fred");
                std::shared_ptr<Argument> secondArg = std::make_shared<StringInput>("l");

                clauseList.push_back(std::make_shared<Clause>(std::make_shared<UsesStrategy>(&usesInterface, true), firstArg, secondArg));

                TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
            }
        }
    }

    SECTION("No Input") {
        SECTION("Uses(p, v)") {
            SECTION("Select v - Output") {
                std::unordered_set<std::string> expectedResult = {"a", "b", "c", "e", "f", "i", "k", "l", "v", "w", "x", "y", "z"};
                std::vector<std::shared_ptr<Clause>> clauseList;

                std::shared_ptr<EntityArgument> selection = std::make_shared<VariableEntity>(&constProcVarInterface, "v", "");
                std::shared_ptr<Argument> firstArg = std::make_shared<ProcedureEntity>(&constProcVarInterface, "p", "");
                std::shared_ptr<Argument> secondArg = std::make_shared<VariableEntity>(&constProcVarInterface, "v", "");

                clauseList.push_back(std::make_shared<Clause>(std::make_shared<UsesStrategy>(&usesInterface, true), firstArg, secondArg));

                TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
            }
        }
    }
}

TEST_CASE("Evaluate Single Select - Single UsesS") {
    initializeInterfaces();
    SECTION("Left Input") {
        SECTION("Uses(3, v) - Output") {
            std::unordered_set<std::string> expectedResult = {"z"};
            std::vector<std::shared_ptr<Clause>> clauseList;

            std::shared_ptr<EntityArgument> selection = std::make_shared<VariableEntity>(&constProcVarInterface, "v", "");
            std::shared_ptr<Argument> firstArg = std::make_shared<StringInput>("3");
            std::shared_ptr<Argument> secondArg = std::make_shared<VariableEntity>(&constProcVarInterface, "v", "");

            clauseList.push_back(std::make_shared<Clause>(std::make_shared<UsesStrategy>(&usesInterface), firstArg, secondArg));

            TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
        }

        SECTION("Uses(1, v) - Empty") {
            std::unordered_set<std::string> expectedResult;
            std::vector<std::shared_ptr<Clause>> clauseList;

            std::shared_ptr<EntityArgument> selection = std::make_shared<VariableEntity>(&constProcVarInterface, "v", "");
            std::shared_ptr<Argument> firstArg = std::make_shared<StringInput>("1");
            std::shared_ptr<Argument> secondArg = std::make_shared<VariableEntity>(&constProcVarInterface, "v", "");

            clauseList.push_back(std::make_shared<Clause>(std::make_shared<UsesStrategy>(&usesInterface), firstArg, secondArg));

            TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
        }
    }

    SECTION("Right Input") {
        SECTION("Uses(s, 'y') - Output") {
            std::unordered_set<std::string> expectedResult = {"12", "13"};
            std::vector<std::shared_ptr<Clause>> clauseList;

            std::shared_ptr<EntityArgument> selection = std::make_shared<StmtStmtEntity>(&stmtInterface, "s", "");;
            std::shared_ptr<Argument> firstArg = std::make_shared<StmtStmtEntity>(&stmtInterface, "s", "");;
            std::shared_ptr<Argument> secondArg = std::make_shared<StringInput>("y");

            clauseList.push_back(std::make_shared<Clause>(std::make_shared<UsesStrategy>(&usesInterface), firstArg, secondArg));

            TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
        }
    }

    SECTION("Both Input") {
        SECTION("Uses(3, 'z')") {
            SECTION("Select v - Output") {
                std::unordered_set<std::string> expectedResult = varSet;
                std::vector<std::shared_ptr<Clause>> clauseList;

                std::shared_ptr<EntityArgument> selection = std::make_shared<VariableEntity>(&constProcVarInterface, "v", "");
                std::shared_ptr<Argument> firstArg = std::make_shared<StringInput>("3");
                std::shared_ptr<Argument> secondArg = std::make_shared<StringInput>("z");

                clauseList.push_back(std::make_shared<Clause>(std::make_shared<UsesStrategy>(&usesInterface), firstArg, secondArg));

                TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
            }
        }

        SECTION("Uses(1, 'x')") {
            SECTION("Select v - Empty") {
                std::unordered_set<std::string> expectedResult;
                std::vector<std::shared_ptr<Clause>> clauseList;

                std::shared_ptr<EntityArgument> selection = std::make_shared<VariableEntity>(&constProcVarInterface, "v", "");
                std::shared_ptr<Argument> firstArg = std::make_shared<StringInput>("1");
                std::shared_ptr<Argument> secondArg = std::make_shared<StringInput>("x");

                clauseList.push_back(std::make_shared<Clause>(std::make_shared<UsesStrategy>(&usesInterface), firstArg, secondArg));

                TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
            }
        }
    }

    SECTION("No Input") {
        SECTION("Uses(s, v)") {
            SECTION("Select v - Output") {
                std::unordered_set<std::string> expectedResult = {"a", "b", "c", "e", "f", "i", "k", "l", "v", "w", "x", "y", "z"};
                std::vector<std::shared_ptr<Clause>> clauseList;

                std::shared_ptr<EntityArgument> selection = std::make_shared<VariableEntity>(&constProcVarInterface, "v", "");
                std::shared_ptr<Argument> firstArg = std::make_shared<StmtStmtEntity>(&stmtInterface, "s", "");;
                std::shared_ptr<Argument> secondArg = std::make_shared<VariableEntity>(&constProcVarInterface, "v", "");

                clauseList.push_back(std::make_shared<Clause>(std::make_shared<UsesStrategy>(&usesInterface), firstArg, secondArg));

                TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
            }

            SECTION("Select s - Output") {
                std::unordered_set<std::string> expectedResult = {"3", "7", "8", "9", "10", "12", "13"};
                std::vector<std::shared_ptr<Clause>> clauseList;

                std::shared_ptr<EntityArgument> selection = std::make_shared<StmtStmtEntity>(&stmtInterface, "s", "");;
                std::shared_ptr<Argument> firstArg = std::make_shared<StmtStmtEntity>(&stmtInterface, "s", "");;
                std::shared_ptr<Argument> secondArg = std::make_shared<VariableEntity>(&constProcVarInterface, "v", "");

                clauseList.push_back(std::make_shared<Clause>(std::make_shared<UsesStrategy>(&usesInterface), firstArg, secondArg));

                TEST_SINGLESELECT_QUERY(selection, clauseList, ErrorStatus::OK, expectedResult);
            }
        }
    }
}
