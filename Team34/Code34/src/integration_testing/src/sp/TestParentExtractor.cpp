#include <filesystem>

#include "catch.hpp"
#include "FileReader.h"

#include "common/tokenizer/Tokenizer.h"
#include "sp/parser/SPParserManager.h"
#include "sp/extractor/ParentRelationVisitor.h"
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

#include "stub/StubParentAdder.cpp"
#include "common/ASTBuilder.h"

TEST_CASE("Evaluate basic parent functionalities - OK - Stub storage contains expected value") {

    std::filesystem::path filePath = std::filesystem::current_path().parent_path();
    std::string separator = std::string(1, std::filesystem::path::preferred_separator);
    std::string file = filePath.string() + separator + "integration_testing" +
        separator + "tests" + separator + "sp_parents_basic.txt";
    std::string src = FileReader::readFile(file);

    StubParentAdder adder;
    ParentRelationVisitor extractor(adder);
    Tokenizer tokenizer;
    SPParserManager parser;

    std::shared_ptr<RootNode> root = parser.parse(tokenizer.tokenize(src));
    
    extractor.begin(*root);
    extractor.transfer();

    SECTION("if") {
        REQUIRE(adder.containsParent(1, 2));
        REQUIRE(adder.containsParent(1, 3));
        REQUIRE(adder.containsParent(1, 4));
        REQUIRE(adder.containsParent(1, 5));
        REQUIRE(!adder.containsParent(5, 1));
    }

    SECTION("Intercontainer") {
        REQUIRE(!adder.containsParent(3, 4));
        REQUIRE(!adder.containsParent(5, 6));
        REQUIRE(!adder.containsParent(1, 6));
    }

    SECTION("while") {
        REQUIRE(adder.containsParent(6, 7));
        REQUIRE(adder.containsParent(6, 8));
    }
}

TEST_CASE("Evaluate nest parent functionalities - OK - Stub storage contains expected value") {

    std::filesystem::path filePath = std::filesystem::current_path().parent_path();
    std::string separator = std::string(1, std::filesystem::path::preferred_separator);
    std::string file = filePath.string() + separator + "integration_testing" +
        separator + "tests" + separator + "sp_parents_nest.txt";
    std::string src = FileReader::readFile(file);

    StubParentAdder adder;
    ParentRelationVisitor extractor(adder);
    Tokenizer tokenizer;
    SPParserManager parser;

    std::shared_ptr<RootNode> root = parser.parse(tokenizer.tokenize(src));

    extractor.begin(*root);
    extractor.transfer();

    SECTION("Intercontainer") {
        REQUIRE(adder.containsParent(1, 2));
        REQUIRE(adder.containsParent(1, 3));
        REQUIRE(adder.containsParent(1, 8));
    }

    SECTION("Multi nest") {
        REQUIRE(!adder.containsParent(1, 4));
        REQUIRE(adder.containsParent(3, 4));
        REQUIRE(adder.containsParent(4, 5));
        REQUIRE(adder.containsParent(4, 6));
        REQUIRE(adder.containsParent(4, 7));
    }

    SECTION("Containers within container") {
        REQUIRE(adder.containsParent(8, 9));
        REQUIRE(adder.containsParent(8, 10));
        REQUIRE(adder.containsParent(8, 12));
    }

}