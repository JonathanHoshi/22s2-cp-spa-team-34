#include <filesystem>

#include "catch.hpp"
#include "FileReader.h"
#include "sp/extractor/CFGExtractorVisitor.h"
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

#include <fstream>
#include <iostream>
#include <filesystem>
#include <string>
#include "stub/StubNextAdder.cpp"
#include "common/ASTBuilder.h"

TEST_CASE("Test CFG extraction - OK - Stub storage contains expected number of entities") {

    std::filesystem::path filePath = std::filesystem::current_path().parent_path();
    std::string separator = std::string(1, std::filesystem::path::preferred_separator);
    std::string file = filePath.string() + separator + "integration_testing"
        + separator + "tests" + separator + "sp_cfg.txt";
    std::string src = FileReader::readFile(file);

    Tokenizer tokenizer;
    SPParserManager parser;
    StubNextAdder adder;
    CFGExtractorVisitor extractor(adder);

    std::shared_ptr<RootNode> root = parser.parse(tokenizer.tokenize(src));

    extractor.begin(*root);
    extractor.transfer();

    SECTION("Basic statements") {
        REQUIRE(adder.containsNext(1, 2));
        REQUIRE(adder.containsNext(2, 3));
    }

    SECTION("Basic negative") {
        REQUIRE_FALSE(adder.containsNext(2, 1));
        REQUIRE_FALSE(adder.containsNext(1, 3));
    }

    SECTION("Next into container") {
        REQUIRE(adder.containsNext(4, 5));
        REQUIRE(adder.containsNext(11, 12));
    }

    SECTION("Next into container negative") {
        REQUIRE_FALSE(adder.containsNext(5, 4));
        REQUIRE_FALSE(adder.containsNext(12, 11));
        REQUIRE_FALSE(adder.containsNext(4, 6));
    }

    SECTION("Within container") {
        REQUIRE(adder.containsNext(6, 7));
        REQUIRE(adder.containsNext(9, 10));
        REQUIRE(adder.containsNext(13, 14));
    }

    SECTION("Within container negative") {
        REQUIRE_FALSE(adder.containsNext(7, 6));
        REQUIRE_FALSE(adder.containsNext(10, 9));
        REQUIRE_FALSE(adder.containsNext(14, 13));
    }

    SECTION("If statement") {
        REQUIRE(adder.containsNext(5, 6));
        REQUIRE(adder.containsNext(5, 9));
        REQUIRE(adder.containsNext(8, 11));
        REQUIRE(adder.containsNext(10, 11));
    }

    SECTION("If statement negative") {
        REQUIRE_FALSE(adder.containsNext(6, 5));
        REQUIRE_FALSE(adder.containsNext(9, 5));
        REQUIRE_FALSE(adder.containsNext(11, 8));
        REQUIRE_FALSE(adder.containsNext(11, 10));
        REQUIRE_FALSE(adder.containsNext(8, 5));
        REQUIRE_FALSE(adder.containsNext(10, 5));
    }

    SECTION("While statement") {
        REQUIRE(adder.containsNext(12, 13));
        REQUIRE(adder.containsNext(12, 15));
        REQUIRE(adder.containsNext(13, 14));
        REQUIRE(adder.containsNext(14, 12));
    }

    SECTION("While statement out") {
        REQUIRE_FALSE(adder.containsNext(13, 12));
        REQUIRE_FALSE(adder.containsNext(14, 13));
        REQUIRE_FALSE(adder.containsNext(12, 14));
        REQUIRE_FALSE(adder.containsNext(14, 15));
    }

    SECTION("Containers within containers") {
        REQUIRE(adder.containsNext(16, 21));
        REQUIRE(adder.containsNext(21, 22));
        REQUIRE(adder.containsNext(22, 23));
        REQUIRE(adder.containsNext(23, 22));
        REQUIRE_FALSE(adder.containsNext(23, 24));
        REQUIRE(adder.containsNext(22, 24));
        REQUIRE(adder.containsNext(24, 21));
    }

    SECTION("Multiple out of containers") {
        REQUIRE(adder.containsNext(19, 32));
        REQUIRE(adder.containsNext(20, 32));
        REQUIRE(adder.containsNext(27, 32));
    }
}