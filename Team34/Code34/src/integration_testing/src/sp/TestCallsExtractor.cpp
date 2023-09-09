#include <filesystem>

#include "catch.hpp"
#include "FileReader.h"
#include "sp/extractor/CallsExtractorVisitor.h"
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
#include "stub/StubCallAdder.cpp"
#include "common/ASTBuilder.h"

TEST_CASE("Test Calls toposorted exception - OK/Exception - Non topo sorted throws error and vice versa") {
    SECTION("Non toposort") {
        std::filesystem::path filePath = std::filesystem::current_path().parent_path();
        std::string separator = std::string(1, std::filesystem::path::preferred_separator);
        std::string file = filePath.string() + separator + "integration_testing" +
            separator + "tests" + separator + "sp_calls_nested.txt";
        std::string src = FileReader::readFile(file);

        Tokenizer tokenizer;
        SPParserManager parser;
        StubCallAdder adder;
        CallsExtractorVisitor extractor(adder);

        std::shared_ptr<RootNode> root = parser.parse(tokenizer.tokenize(src));

        REQUIRE_THROWS(extractor.begin(*root));
    }

    SECTION("Non toposort") {
        std::filesystem::path filePath = std::filesystem::current_path().parent_path();
        std::string separator = std::string(1, std::filesystem::path::preferred_separator);
        std::string file = filePath.string() + separator + "integration_testing"
            + separator + "tests" + separator + "sp_calls_nested_topo.txt";
        std::string src = FileReader::readFile(file);

        Tokenizer tokenizer;
        SPParserManager parser;
        StubCallAdder adder;
        CallsExtractorVisitor extractor(adder);

        std::shared_ptr<RootNode> root = parser.parse(tokenizer.tokenize(src));

        REQUIRE_NOTHROW(extractor.begin(*root));
    }
}

TEST_CASE("Test Calls extraction - OK - Stub contains expected value") {
    std::filesystem::path filePath = std::filesystem::current_path().parent_path();
    std::string separator = std::string(1, std::filesystem::path::preferred_separator);
    std::string file = filePath.string() + separator + "integration_testing"
        + separator + "tests" + separator + "sp_calls_nested_topo.txt";
    std::string src = FileReader::readFile(file);

    Tokenizer tokenizer;
    SPParserManager parser;
    StubCallAdder adder;
    CallsExtractorVisitor extractor(adder);

    std::shared_ptr<RootNode> root = parser.parse(tokenizer.tokenize(src));

    extractor.begin(*root);
    extractor.transfer();

    SECTION("Direct calls") {
        REQUIRE(adder.containsCall("a1", "a2"));
        REQUIRE(adder.containsCall("a1", "a3"));
        REQUIRE(adder.containsCall("a2", "a3"));
        REQUIRE(adder.containsCall("a3", "a4"));
        REQUIRE(adder.containsCall("a3", "a6"));
        REQUIRE(adder.containsCall("a4", "a5"));
        REQUIRE(adder.containsCall("a6", "a5"));
        REQUIRE(adder.containsCall("a5", "a7"));
    }

    SECTION("Direct calls Negative") {
        REQUIRE_FALSE(adder.containsCall("a2", "a1"));
        REQUIRE_FALSE(adder.containsCall("a3", "a1"));
        REQUIRE_FALSE(adder.containsCall("a3", "a2"));
        REQUIRE_FALSE(adder.containsCall("a4", "a3"));
        REQUIRE_FALSE(adder.containsCall("a6", "a3"));
        REQUIRE_FALSE(adder.containsCall("a5", "a4"));
        REQUIRE_FALSE(adder.containsCall("a5", "a6"));
        REQUIRE_FALSE(adder.containsCall("a7", "a5"));
    }

    SECTION("Calls != CallsT") {
        REQUIRE_FALSE(adder.containsCall("a1", "a7"));
        REQUIRE_FALSE(adder.containsCall("a1", "a6"));
        REQUIRE_FALSE(adder.containsCall("a1", "a4"));

        REQUIRE_FALSE(adder.containsCall("a2", "a7"));
        REQUIRE_FALSE(adder.containsCall("a3", "a7"));
        REQUIRE_FALSE(adder.containsCall("a4", "a7"));
        REQUIRE_FALSE(adder.containsCall("a6", "a7"));
    }

    SECTION("CallsT") {
        REQUIRE(adder.containsCallT("a1", "a2"));
        REQUIRE(adder.containsCallT("a1", "a3"));
        REQUIRE(adder.containsCallT("a1", "a4"));
        REQUIRE(adder.containsCallT("a1", "a5"));
        REQUIRE(adder.containsCallT("a1", "a6"));
        REQUIRE(adder.containsCallT("a1", "a7"));

        REQUIRE(adder.containsCallT("a2", "a3"));
        REQUIRE(adder.containsCallT("a2", "a4"));
        REQUIRE(adder.containsCallT("a2", "a6"));
        REQUIRE(adder.containsCallT("a2", "a5"));
        REQUIRE(adder.containsCallT("a2", "a7"));

        REQUIRE(adder.containsCallT("a3", "a4"));
        REQUIRE(adder.containsCallT("a3", "a6"));
        REQUIRE(adder.containsCallT("a3", "a5"));
        REQUIRE(adder.containsCallT("a3", "a7"));

        REQUIRE(adder.containsCallT("a4", "a5"));
        REQUIRE(adder.containsCallT("a4", "a7"));

        REQUIRE(adder.containsCallT("a6", "a5"));
        REQUIRE(adder.containsCallT("a6", "a7"));

        REQUIRE(adder.containsCallT("a5", "a7"));
    }

    SECTION("CallsT Negative") {
        REQUIRE_FALSE(adder.containsCallT("a2", "a1"));
        REQUIRE_FALSE(adder.containsCallT("a3", "a1"));
        REQUIRE_FALSE(adder.containsCallT("a4", "a1"));
        REQUIRE_FALSE(adder.containsCallT("a5", "a1"));
        REQUIRE_FALSE(adder.containsCallT("a6", "a1"));
        REQUIRE_FALSE(adder.containsCallT("a7", "a1"));

        REQUIRE_FALSE(adder.containsCallT("a3", "a2"));
        REQUIRE_FALSE(adder.containsCallT("a4", "a2"));
        REQUIRE_FALSE(adder.containsCallT("a6", "a2"));
        REQUIRE_FALSE(adder.containsCallT("a5", "a2"));
        REQUIRE_FALSE(adder.containsCallT("a7", "a2"));

        REQUIRE_FALSE(adder.containsCallT("a4", "a3"));
        REQUIRE_FALSE(adder.containsCallT("a6", "a3"));
        REQUIRE_FALSE(adder.containsCallT("a5", "a3"));
        REQUIRE_FALSE(adder.containsCallT("a7", "a3"));

        REQUIRE_FALSE(adder.containsCallT("a5", "a4"));
        REQUIRE_FALSE(adder.containsCallT("a7", "a4"));

        REQUIRE_FALSE(adder.containsCallT("a5", "a6"));
        REQUIRE_FALSE(adder.containsCallT("a7", "a6"));

        REQUIRE_FALSE(adder.containsCallT("a7", "a5"));
    }
}

TEST_CASE("Test Multipath calls extraction - OK - Stub contains expected value") {
    std::filesystem::path filePath = std::filesystem::current_path().parent_path();
    std::string separator = std::string(1, std::filesystem::path::preferred_separator);
    std::string file = filePath.string() + separator + "integration_testing"
        + separator + "tests" + separator + "sp_calls_multipath_topo.txt";
    std::string src = FileReader::readFile(file);

    Tokenizer tokenizer;
    SPParserManager parser;
    StubCallAdder adder;
    CallsExtractorVisitor extractor(adder);

    std::shared_ptr<RootNode> root = parser.parse(tokenizer.tokenize(src));

    extractor.begin(*root);
    extractor.transfer();

    SECTION("Basic test") {
        REQUIRE(adder.containsCall("a1", "a2"));
        REQUIRE(adder.containsCall("a2", "a3"));
        REQUIRE(adder.containsCall("a3", "a4"));
        REQUIRE(adder.containsCall("a4", "a8"));

        REQUIRE(adder.containsCall("a1", "a5"));
        REQUIRE(adder.containsCall("a5", "a6"));
        REQUIRE(adder.containsCall("a6", "a7"));
        REQUIRE(adder.containsCall("a7", "a8"));

        REQUIRE(adder.containsCallT("a1", "a8"));
        REQUIRE(adder.containsCallT("a2", "a8"));
        REQUIRE(adder.containsCallT("a5", "a8"));
    }

    SECTION("Multipaths do not cross") {
        REQUIRE_FALSE(adder.containsCallT("a2", "a5"));
        REQUIRE_FALSE(adder.containsCallT("a2", "a6"));
        REQUIRE_FALSE(adder.containsCallT("a2", "a7"));

        REQUIRE_FALSE(adder.containsCallT("a5", "a2"));
        REQUIRE_FALSE(adder.containsCallT("a5", "a3"));
        REQUIRE_FALSE(adder.containsCallT("a5", "a4"));

        REQUIRE(adder.containsCallT("a2", "a8"));
        REQUIRE(adder.containsCallT("a5", "a8"));
    }
}

