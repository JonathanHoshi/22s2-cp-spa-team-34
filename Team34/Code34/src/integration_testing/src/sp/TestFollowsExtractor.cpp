#include <filesystem>

#include "FileReader.h"
#include "catch.hpp"

#include "common/tokenizer/Tokenizer.h"
#include "sp/parser/SPParserManager.h"
#include "sp/extractor/FollowRelationVisitor.h"
#include "stub/StubFollowsAdder.cpp"
#include "common/ASTBuilder.h"
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

TEST_CASE("Evaluate Follows basic - OK - Stub storage contains expected value") {

    std::filesystem::path filePath = std::filesystem::current_path().parent_path();
    std::string separator = std::string(1, std::filesystem::path::preferred_separator);
    std::string file = filePath.string() + separator + "integration_testing" +
        separator + "tests" + separator + "sp_follows_basic.txt";
    std::string src = FileReader::readFile(file);

    StubFollowsAdder adder;
    Tokenizer tokenizer;
    SPParserManager parser;
    FollowRelationVisitor extractor(adder);

    std::shared_ptr<RootNode> root = parser.parse(tokenizer.tokenize(src));

    extractor.begin(*root);
    extractor.transfer();

    REQUIRE(adder.containsFollow("1", "2"));
    REQUIRE(adder.containsFollow("2", "3"));
    REQUIRE(!adder.containsFollow("1", "3"));
}

TEST_CASE("Evaluate Follows container - OK - Stub storage contains expected value") {

    std::filesystem::path filePath = std::filesystem::current_path().parent_path();
    std::string separator = std::string(1, std::filesystem::path::preferred_separator);
    std::string file = filePath.string() + separator + "integration_testing"
        + separator + "tests" + separator + "sp_follows_container.txt";
    std::string src = FileReader::readFile(file);

    StubFollowsAdder adder;
    Tokenizer tokenizer;
    SPParserManager parser;
    FollowRelationVisitor extractor(adder);
    std::shared_ptr<RootNode> root = parser.parse(tokenizer.tokenize(src));

    extractor.begin(*root);
    extractor.transfer();

    SECTION("Container follows") {
        REQUIRE(adder.containsFollow("1", "6"));
        REQUIRE(adder.containsFollow("6", "8"));
        REQUIRE(!adder.containsFollow("1", "8"));
    }

    SECTION("Basic statement within if follow") {
        REQUIRE(adder.containsFollow("2", "3"));
        REQUIRE(!adder.containsFollow("3", "4"));
        REQUIRE(adder.containsFollow("4", "5"));
    }

    SECTION("Statements within container don't follow") {
        REQUIRE(!adder.containsFollow("5", "6"));
        REQUIRE(!adder.containsFollow("6", "7"));
        REQUIRE(!adder.containsFollow("7", "8"));
    }

    SECTION("Containers within container follow") {
        REQUIRE(adder.containsFollow("9", "12"));
    }
}