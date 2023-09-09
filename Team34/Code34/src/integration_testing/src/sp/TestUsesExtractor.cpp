#include <filesystem>

#include "catch.hpp"
#include "FileReader.h"

#include "common/tokenizer/Tokenizer.h"
#include "sp/parser/SPParserManager.h"
#include "sp/extractor/UsesRelationVisitor.h"

#include "stub/StubUsesAdder.cpp"
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

TEST_CASE("Evaluate Uses basic - OK - Stub storage contains expected value") {

    std::filesystem::path filePath = std::filesystem::current_path().parent_path();
    std::string separator = std::string(1, std::filesystem::path::preferred_separator);
    std::string file = filePath.string() + separator + "integration_testing" +
        separator + "tests" + separator + "sp_uses_basic.txt";
    std::string src = FileReader::readFile(file);

    StubUsesAdder adder;
    UsesRelationVisitor extractor(adder);
    Tokenizer tokenizer;
    SPParserManager parser;

    std::shared_ptr<RootNode> root = parser.parse(tokenizer.tokenize(src));

    extractor.begin(*root);
    extractor.transfer();

    SECTION("Assignment/Factors/Terms") {
        REQUIRE(adder.containsUsesS(1, "a"));
        REQUIRE(adder.containsUsesS(1, "c"));
        REQUIRE(adder.containsUsesS(1, "b"));
        REQUIRE(adder.containsUsesS(1, "y"));
        REQUIRE(adder.containsUsesS(1, "z"));
        REQUIRE(!adder.containsUsesS(1, "x"));
    }

    SECTION("Print/Read/Number assignment") {
        REQUIRE(!adder.containsUsesS(4, "k"));
        REQUIRE(!adder.containsUsesS(2, "t"));
        REQUIRE(!adder.containsUsesS(2, "1"));
        REQUIRE(adder.containsUsesS(3, "a"));
    }
}

TEST_CASE("Evaluate Uses nest - OK - Stub storage contains expected value") {
    std::filesystem::path filePath = std::filesystem::current_path().parent_path();
    std::string separator = std::string(1, std::filesystem::path::preferred_separator);
    std::string file = filePath.string() + separator + "integration_testing" +
        separator + "tests" + separator + "sp_uses_nest.txt";
    std::string src = FileReader::readFile(file);

    StubUsesAdder adder;
    UsesRelationVisitor extractor(adder);
    Tokenizer tokenizer;
    SPParserManager parser;

    std::shared_ptr<RootNode> root = parser.parse(tokenizer.tokenize(src));
    
    extractor.begin(*root);
    extractor.transfer();

    SECTION("condition/equality") {
        REQUIRE(adder.containsUsesS(1, "h"));
        REQUIRE(adder.containsUsesS(10, "o"));
        REQUIRE(adder.containsUsesS(10, "p"));
    }

    SECTION("statements within if/while") {
        REQUIRE(adder.containsUsesS(1, "a"));
        REQUIRE(adder.containsUsesS(1, "b"));
        REQUIRE(adder.containsUsesS(1, "c"));
        REQUIRE(adder.containsUsesS(1, "e"));
        REQUIRE(adder.containsUsesS(1, "f"));
        REQUIRE(adder.containsUsesS(1, "g"));
        REQUIRE(adder.containsUsesS(1, "i"));
        REQUIRE(!adder.containsUsesS(1, "k"));
        REQUIRE(!adder.containsUsesS(1, "j"));

        REQUIRE(adder.containsUsesS(10, "d"));
        REQUIRE(adder.containsUsesS(10, "e"));
        REQUIRE(!adder.containsUsesS(10, "t"));
    }
}