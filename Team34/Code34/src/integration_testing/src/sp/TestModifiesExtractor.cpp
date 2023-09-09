#include <filesystem>

#include "catch.hpp"
#include "FileReader.h"
#include "common/tokenizer/Tokenizer.h"
#include "sp/parser/SPParserManager.h"
#include "sp/extractor/ModifyRelationVisitor.h"
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

#include "stub/StubModifiesAdder.cpp"
#include "common/ASTBuilder.h"

TEST_CASE("Evaluate basic statements modifies - OK - Stub storage contains expected value") {
    std::filesystem::path filePath = std::filesystem::current_path().parent_path();
    std::string separator = std::string(1, std::filesystem::path::preferred_separator);
    std::string file = filePath.string() + separator + "integration_testing"
        + separator + "tests" + separator + "sp_modifies_basic.txt";
    std::string src = FileReader::readFile(file);


    StubModifiesAdder adder;
    ModifyRelationVisitor extractor(adder);
    Tokenizer tokenizer;
    SPParserManager parser;
    std::shared_ptr<RootNode> root = parser.parse(tokenizer.tokenize(src));
    
    extractor.begin(*root);
    extractor.transfer();

    REQUIRE(adder.containsModifiesS(1, "x"));
    REQUIRE(adder.containsModifiesS(2, "x"));
    REQUIRE(!adder.containsModifiesS(3, "z"));
}

TEST_CASE("Evaluate containers statements modifies - OK - Stub storage contains expected value") {

    std::filesystem::path filePath = std::filesystem::current_path().parent_path();
    std::string separator = std::string(1, std::filesystem::path::preferred_separator);
    std::string file = filePath.string() + separator + "integration_testing"
        + separator + "tests" + separator + "sp_modifies_container.txt";
    std::string src = FileReader::readFile(file);

    StubModifiesAdder adder;
    ModifyRelationVisitor extractor(adder);
    Tokenizer tokenizer;
    SPParserManager parser;
    std::shared_ptr<RootNode> root = parser.parse(tokenizer.tokenize(src));
    
    extractor.begin(*root);
    extractor.transfer();

    SECTION("if") {
        REQUIRE(!adder.containsModifiesS(1, "b"));

        REQUIRE(adder.containsModifiesS(2, "x"));
        REQUIRE(adder.containsModifiesS(3, "y"));
        REQUIRE(adder.containsModifiesS(4, "t"));
        REQUIRE(!adder.containsModifiesS(5, "a"));

        REQUIRE(adder.containsModifiesS(1, "x"));
        REQUIRE(adder.containsModifiesS(1, "y"));
        REQUIRE(adder.containsModifiesS(1, "t"));

        REQUIRE(!adder.containsModifiesS(1, "a"));
    }

    SECTION("while") {
        REQUIRE(!adder.containsModifiesS(6, "r"));
        REQUIRE(adder.containsModifiesS(7, "x"));
        REQUIRE(!adder.containsModifiesS(8, "k"));

        REQUIRE(adder.containsModifiesS(6, "x"));
        REQUIRE(!adder.containsModifiesS(6, "k"));
    }
}