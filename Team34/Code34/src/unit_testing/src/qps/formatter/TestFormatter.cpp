#include <list>

#include "catch.hpp"
#include "qps/argument/entity/ProcedureEntity.h"
#include "qps/argument/entity/VariableEntity.h"
#include "qps/argument/entity/stmt/ReadStmtEntity.h"
#include "qps/formatter/Formatter.h"
#include "../evaluator/stub_entity/StubConstProcVarGetter.cpp"
#include "../evaluator/stub_entity/StubStmtGetter.cpp"

namespace test_entity_formatter {
    StubStmtGetter stmtInterface;
    StubConstProcVarGetter constProcVarInterface;

    std::unordered_map<int, std::string> readMap = {{2, "sp"},
        {7, "qps"},
        {9, "pkb"}};
    std::unordered_map<int, std::string> printMap = {{5, "sp"},
        {11, "pkb"},
        {15, "qps"}};
    std::unordered_map<int, std::string> callStmtMap = {{1, "cx"},
        {4, "jon"},
        {13, "jon"}};
    std::unordered_set<int> ifStmtSet = {10};
    std::unordered_set<int> whileStmtSet = {14};
    std::unordered_set<int> assignStmtSet = {3, 6, 8, 12};
    std::unordered_set<int> constSet = {1, 2, 7};
    std::unordered_set<std::string> varSet = {"pkb", "qps", "sp", "a", "b", "c", "d", "e", "f", "g", "h", "i", "j"};
    std::unordered_set<std::string> procSet = {"cx", "fred", "jon", "nat", "ryan"};

    void initializeInterfaces() {
        constProcVarInterface.setVarEntries(varSet);
        constProcVarInterface.setProcEntries(procSet);
        constProcVarInterface.setConstEntries(constSet);
        stmtInterface.setReadStmtEntries(readMap);
        stmtInterface.setPrintStmtEntries(printMap);
        stmtInterface.setCallStmtEntries(callStmtMap);
        stmtInterface.setIfStmtEntries(ifStmtSet);
        stmtInterface.setWhileStmtEntries(whileStmtSet);
        stmtInterface.setAssignStmtEntries(assignStmtSet);
    }

    // for expected results
    std::unordered_set<int> stmtSet = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
}


using namespace test_entity_formatter;

inline std::unordered_set<std::string> convertListToSet(std::list<std::string> list) {
    return std::unordered_set<std::string>(list.begin(), list.end());
}

// Format: "Format <NAME> - <ErrorStatus> - <Result>"

TEST_CASE("Format Single Variable Select - OK - x, y, z") {
    std::shared_ptr<Argument> var = std::make_shared<VariableEntity>(&constProcVarInterface, "v", "");
    std::list<std::string> expectedOutput = {"x", "y", "z"};

    AbstractQuery query;
    query.updateStatus(ErrorStatus::OK);
    query.addSelection(var);

    std::unordered_set<std::string> inputArr = convertListToSet(expectedOutput);
    query.getResult()->addSynonymGroup(var->getValue(), inputArr);

    Formatter formatter;

    std::list<std::string> output = formatter.formatResult(query);

    REQUIRE(output == expectedOutput);
}

TEST_CASE("Format Single Procedure Select - OK - fred, nat, jon") {
    std::shared_ptr<Argument> proc = std::make_shared<ProcedureEntity>(&constProcVarInterface, "p", "");
    std::list<std::string> inputList = {"jon", "nat", "fred"};
    std::list<std::string> expectedOutput = {"fred", "jon", "nat"};

    AbstractQuery query;
    query.updateStatus(ErrorStatus::OK);
    query.addSelection(proc);

    std::unordered_set<std::string> inputArr = convertListToSet(inputList);
    query.getResult()->addSynonymGroup(proc->getValue(), inputArr);

    Formatter formatter;

    std::list<std::string> output = formatter.formatResult(query);

    REQUIRE(output == expectedOutput);
}

TEST_CASE("Format Syntax Error - SyntaxError - SyntaxError") {
    std::shared_ptr<Argument> proc = std::make_shared<ProcedureEntity>(&constProcVarInterface, "p", "");
    std::list<std::string> inputList = {"fred", "jon", "nat"};
    std::list<std::string> expectedOutput = {"SyntaxError"};

    AbstractQuery query;
    query.updateStatus(ErrorStatus::SYNTAX);
    query.addSelection(proc);

    std::unordered_set<std::string> inputArr = convertListToSet(inputList);
    query.getResult()->addSynonymGroup(proc->getValue(), inputArr);

    Formatter formatter;

    std::list<std::string> output = formatter.formatResult(query);

    REQUIRE(output == expectedOutput);
}

TEST_CASE("Format Semantic Error - SemanticError - SemanticError") {
    std::shared_ptr<Argument> proc = std::make_shared<ProcedureEntity>(&constProcVarInterface, "p", "");
    std::list<std::string> inputList = {"fred", "jon", "nat"};
    std::list<std::string> expectedOutput = {"SemanticError"};

    AbstractQuery query;
    query.updateStatus(ErrorStatus::SEMANTIC);
    query.addSelection(proc);

    std::unordered_set<std::string> inputArr = convertListToSet(inputList);
    query.getResult()->addSynonymGroup(proc->getValue(), inputArr);

    Formatter formatter;

    std::list<std::string> output = formatter.formatResult(query);

    REQUIRE(output == expectedOutput);
}

TEST_CASE("Format Single Variable Select BOOLEAN - OK - x, y, z") {
    std::shared_ptr<Argument> var = std::make_shared<VariableEntity>(&constProcVarInterface, "v", "");
    std::list<std::string> expectedOutput = {"TRUE"};

    AbstractQuery query;
    query.setSelectBoolean(true);
    query.updateStatus(ErrorStatus::OK);
    query.addSelection(var);

    std::unordered_set<std::string> inputArr = convertListToSet(expectedOutput);
    query.getResult()->addSynonymGroup(var->getValue(), inputArr);

    Formatter formatter;

    std::list<std::string> output = formatter.formatResult(query);

    REQUIRE(output == expectedOutput);
}

TEST_CASE("Format Select BOOLEAN - OK - EMPTY SELECTION") {
    std::list<std::string> expectedOutput = {"TRUE"};

    AbstractQuery query;
    query.setSelectBoolean(true);
    query.updateStatus(ErrorStatus::OK);

    Formatter formatter;

    std::list<std::string> output = formatter.formatResult(query);

    REQUIRE(output == expectedOutput);
}

TEST_CASE("Format Select TUPLE - OK - Select <p, v>") {
    std::shared_ptr<Argument> proc = std::make_shared<ProcedureEntity>(&constProcVarInterface, "p", "");
    std::shared_ptr<Argument> var = std::make_shared<VariableEntity>(&constProcVarInterface, "v", "");
    std::list<std::string> expectedOutput = {"proc1 x", "proc1 y", "proc1 z"
        , "proc2 x", "proc2 y", "proc2 z"
        , "proc3 x", "proc3 y", "proc3 z"};

    AbstractQuery query;
    query.updateStatus(ErrorStatus::OK);
    query.addSelection(proc);
    query.addSelection(var);
    std::unordered_set<std::string> procSet = { "proc1", "proc2", "proc3" };
    std::unordered_set<std::string> varSet = { "x", "y", "z" };
    query.getResult()->addSynonymGroup(proc->getValue(), procSet);
    query.getResult()->addSynonymGroup(var->getValue(), varSet);

    Formatter formatter;

    std::list<std::string> output = formatter.formatResult(query);

    REQUIRE(output == expectedOutput);
}

TEST_CASE("Format Select TUPLE - OK - Select <p, p>") {
    std::shared_ptr<Argument> proc = std::make_shared<ProcedureEntity>(&constProcVarInterface, "p", "");
    std::list<std::string> expectedOutput = {"proc1 proc1", "proc2 proc2", "proc3 proc3"};

    AbstractQuery query;
    query.updateStatus(ErrorStatus::OK);
    query.addSelection(proc);
    query.addSelection(proc);
    std::unordered_set<std::string> procSet = { "proc1", "proc2", "proc3" };
    query.getResult()->addSynonymGroup(proc->getValue(), procSet);

    Formatter formatter;

    std::list<std::string> output = formatter.formatResult(query);

    REQUIRE(output == expectedOutput);
}

TEST_CASE("Format Select TUPLE w Attr - OK - Select <r.stmt#, r.varName>") {
    initializeInterfaces();
    std::shared_ptr<Argument> read1 = std::make_shared<ReadStmtEntity>(&stmtInterface, "r", "stmt#");
    std::shared_ptr<Argument> read2 = std::make_shared<ReadStmtEntity>(&stmtInterface, "r", "varName");
    std::list<std::string> expectedOutput = {"2 sp", "7 qps", "9 pkb"};

    AbstractQuery query;
    query.updateStatus(ErrorStatus::OK);
    query.addSelection(read1);
    query.addSelection(read2);
    std::unordered_set<std::string> readStmtSet = { "2", "7", "9" };
    query.getResult()->addSynonymGroup(read1->getValue(), readStmtSet);

    Formatter formatter;

    std::list<std::string> output = formatter.formatResult(query);

    REQUIRE(output == expectedOutput);
}

TEST_CASE("Format Select TUPLE w Attr - OK - Select <r.stmt#, r1.varName>") {
    initializeInterfaces();
    std::shared_ptr<Argument> read1 = std::make_shared<ReadStmtEntity>(&stmtInterface, "r", "stmt#");
    std::shared_ptr<Argument> read2 = std::make_shared<ReadStmtEntity>(&stmtInterface, "r1", "varName");
    std::list<std::string> expectedOutput = {"2 pkb", "2 qps", "2 sp", "7 pkb", "7 qps", "7 sp", "9 pkb", "9 qps", "9 sp"};

    AbstractQuery query;
    query.updateStatus(ErrorStatus::OK);
    query.addSelection(read1);
    query.addSelection(read2);
    std::unordered_set<std::string> readStmtSet = { "2", "7", "9" };
    query.getResult()->addSynonymGroup(read1->getValue(), readStmtSet);
    query.getResult()->addSynonymGroup(read2->getValue(), readStmtSet);

    Formatter formatter;

    std::list<std::string> output = formatter.formatResult(query);

    REQUIRE(output == expectedOutput);
}
