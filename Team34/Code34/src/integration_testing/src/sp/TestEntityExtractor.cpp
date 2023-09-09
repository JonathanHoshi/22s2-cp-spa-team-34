#include <filesystem>

#include "catch.hpp"
#include "FileReader.h"
#include "sp/extractor/EntityExtractorVisitor.h"
#include "common/tokenizer/Tokenizer.h"
#include "sp/parser/SPParserManager.h"
#include "sp/node/AssignNode.h"
#include "sp/node/CallNode.h"
#include "sp/node/ConstantNode.h"
#include "sp/node/IfNode.h"
#include "sp/node/OperatorNode.h"
#include "sp/node/PrintNode.h"
#include "sp/node/ProcedureNode.h"
#include "sp/node/ReadNode.h"
#include "sp/node/RootNode.h"
#include "sp/node/StmtLstNode.h"
#include "sp/node/StmtNode.h"
#include "sp/node/VariableNode.h"
#include "sp/node/WhileNode.h"

#include "stub/StubStmtAdder.cpp"
#include "stub/StubProcAdder.cpp"
#include "stub/StubConstAdder.cpp"
#include "stub/StubVarAdder.cpp"
#include "common/ASTBuilder.h"

// Format: "Format <NAME> - <ErrorStatus> - <Result>"

TEST_CASE("Test extraction entity basic count - OK - Stub storage contains expected number of entities") {

    std::filesystem::path filePath = std::filesystem::current_path().parent_path();
    std::string separator = std::string(1, std::filesystem::path::preferred_separator);
    std::string file = filePath.string() + separator + "integration_testing"
        + separator + "tests" + separator + "sp_entities_basic.txt";
    std::string src = FileReader::readFile(file);

    Tokenizer tokenizer;
    SPParserManager parser;

    StubStmtAdder stmtAdder;
    StubProcAdder procAdder;
    StubConstAdder constAdder;
    StubVarAdder varAdder;

    EntityExtractorVisitor visitor(stmtAdder, procAdder, constAdder, varAdder);
    std::shared_ptr<RootNode> root = parser.parse(tokenizer.tokenize(src));

    visitor.begin(*root);
    visitor.transfer();

    REQUIRE(stmtAdder.getReadCount() == 2);
    REQUIRE(stmtAdder.getPrintCount() == 3);
    REQUIRE(varAdder.getVarCount() == 12);
    REQUIRE(constAdder.getConstCount() == 4);
    REQUIRE(procAdder.getProcedureCount() == 3);
    REQUIRE(stmtAdder.getCallCount() == 2);
    REQUIRE(stmtAdder.getAssignCount() == 9);
    REQUIRE(stmtAdder.getIfCount() == 2);
    REQUIRE(stmtAdder.getWhileCount() == 2);
}

TEST_CASE("Test extraction entity containers count - OK - Stub storage contains expected number of entities") {

    std::filesystem::path filePath = std::filesystem::current_path().parent_path();
    std::string separator = std::string(1, std::filesystem::path::preferred_separator);
    std::string file = filePath.string() + separator + "integration_testing" +
        separator + "tests" + separator + "sp_entities_containers.txt";
    std::string src = FileReader::readFile(file);

    Tokenizer tokenizer;
    SPParserManager parser;

    StubStmtAdder stmtAdder;
    StubProcAdder procAdder;
    StubConstAdder constAdder;
    StubVarAdder varAdder;

    EntityExtractorVisitor visitor(stmtAdder, procAdder, constAdder, varAdder);
    std::shared_ptr<RootNode> root = parser.parse(tokenizer.tokenize(src));

    visitor.begin(*root);
    visitor.transfer();

    REQUIRE(stmtAdder.getReadCount() == 1);
    REQUIRE(stmtAdder.getPrintCount() == 1);
    REQUIRE(varAdder.getVarCount() == 15);
    REQUIRE(constAdder.getConstCount() == 11);
    REQUIRE(procAdder.getProcedureCount() == 1);
    REQUIRE(stmtAdder.getCallCount() == 1);
    REQUIRE(stmtAdder.getAssignCount() == 3);
    REQUIRE(stmtAdder.getIfCount() == 2);
    REQUIRE(stmtAdder.getWhileCount() == 2);
}


