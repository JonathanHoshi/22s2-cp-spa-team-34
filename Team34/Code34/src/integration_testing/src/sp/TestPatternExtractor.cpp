#include <filesystem>

#include "catch.hpp"
#include "FileReader.h"

#include "common/tokenizer/Tokenizer.h"
#include "sp/parser/SPParserManager.h"
#include "sp/extractor/PatternExtractorVisitor.h"
#include "stub/StubAssignPatternAdder.cpp"
#include "stub/StubWhilePatternAdder.cpp"
#include "stub/StubIfPatternAdder.cpp"
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

TEST_CASE("Evaluate Pattern - OK - Stub storage contains expected value") {

    std::filesystem::path filePath = std::filesystem::current_path().parent_path();
    std::string separator = std::string(1, std::filesystem::path::preferred_separator);
    std::string file = filePath.string() + separator + "integration_testing" +
        separator + "tests" + separator + "sp_pattern.txt";
    std::string src = FileReader::readFile(file);

    StubAssignPatternAdder assignAdder;
    StubIfPatternAdder ifAdder;
    StubWhilePatternAdder whileAdder;
    PatternExtractorVisitor extractor(assignAdder, ifAdder, whileAdder);
    Tokenizer tokenizer;
    SPParserManager parser;

    std::shared_ptr<RootNode> root = parser.parse(tokenizer.tokenize(src));

    extractor.begin(*root);
    extractor.transfer();

    SECTION("Basic Full") {
        REQUIRE(assignAdder.checkFullPattern(1, "x", "x + y + z"));
        REQUIRE(!assignAdder.checkFullPattern(1, "x", "y + z"));
        REQUIRE(!assignAdder.checkFullPattern(1, "y", "x + y + z"));
        REQUIRE(!assignAdder.checkFullPattern(2, "x", "x + y + z"));
    }

    SECTION("Left != Right") {
        REQUIRE(!assignAdder.checkPatternExist(1, "y"));
    }

    SECTION("Basic Partial") {
        REQUIRE(assignAdder.checkPartialPattern(1, "x", "x + y"));
        REQUIRE(assignAdder.checkPartialPattern(1, "x", "x + y + z"));

        REQUIRE(!assignAdder.checkPartialPattern(1, "x", "y + z"));
        REQUIRE(!assignAdder.checkPartialPattern(1, "y", "x + y"));
        REQUIRE(!assignAdder.checkPartialPattern(2, "x", "x + y"));
    }

    SECTION("Order of operations") {
        REQUIRE(assignAdder.checkFullPattern(2, "x", "x + y * z"));
        REQUIRE(!assignAdder.checkPartialPattern(2, "x", "x + y"));
        REQUIRE(assignAdder.checkPartialPattern(2, "x", "y * z"));
        REQUIRE(assignAdder.checkPartialPattern(2, "x", "y * z"));
    }
}

TEST_CASE("Evaluate Advanced assign Pattern - OK - Stub storage contains expected value") {

    filesystem::path filePath = filesystem::current_path().parent_path();
    string separator = string(1, filesystem::path::preferred_separator);
    string file = filePath.string() + separator + "integration_testing" +
        separator + "tests" + separator + "sp_assign_pattern_advanced.txt";
    string src = FileReader::readFile(file);

    StubAssignPatternAdder assignAdder;
    StubIfPatternAdder ifAdder;
    StubWhilePatternAdder whileAdder;
    PatternExtractorVisitor extractor(assignAdder, ifAdder, whileAdder);
    Tokenizer tokenizer;
    SPParserManager parser;

    std::shared_ptr<RootNode> root = parser.parse(tokenizer.tokenize(src));
    
    extractor.begin(*root);
    extractor.transfer();

    SECTION("Brackets") {
        REQUIRE(assignAdder.checkFullPattern(1, "x", "x + y + z + y"));
        REQUIRE(assignAdder.checkPartialPattern(1, "x", "x + y"));
        REQUIRE(assignAdder.checkPartialPattern(1, "x", "(((x + y)))"));

        REQUIRE(!assignAdder.checkFullPattern(2, "x", "x + y + z + y"));
        REQUIRE(assignAdder.checkFullPattern(2, "x", "x + (y + z) + y"));
        REQUIRE(!assignAdder.checkPartialPattern(2, "x", "x + y"));
        REQUIRE(assignAdder.checkPartialPattern(2, "x", "y + z"));

        REQUIRE(assignAdder.checkFullPattern(3, "x", "x + y + 3 + z + y"));
        REQUIRE(assignAdder.checkPartialPattern(3, "x", "x + y + 3"));
        REQUIRE(!assignAdder.checkPartialPattern(3, "x", "z + y"));

        REQUIRE(assignAdder.checkPartialPattern(4, "x", "x + y"));
        REQUIRE(assignAdder.checkPartialPattern(4, "x", "3 + z"));
        REQUIRE(assignAdder.checkPartialPattern(4, "x", "x + y + (3 + z)"));
        REQUIRE(!assignAdder.checkPartialPattern(4, "x", "(3 + z) + y"));
    }

    SECTION("Containers conditions don't apply to assign patterns") {
        REQUIRE(!assignAdder.checkPatternExist(5, "x"));
        REQUIRE(!assignAdder.checkPatternExist(5, "y"));
        REQUIRE(!assignAdder.checkPatternExist(9, "x"));
        REQUIRE(!assignAdder.checkPatternExist(9, "y"));
        REQUIRE(!assignAdder.checkPatternExist(9, "z"));
    }

    SECTION("Statements within containers") {
        REQUIRE(!assignAdder.checkPatternExist(6, "a"));
        REQUIRE(assignAdder.checkFullPattern(7, "a", "b + c * d"));
    }

    SECTION("Keywords within statements") {
        REQUIRE(assignAdder.checkFullPattern(11, "print", "read + procedure * 3"));
    }

    SECTION("While Pattern Basic") {
        REQUIRE(whileAdder.contains(9, "x"));
        REQUIRE(whileAdder.contains(9, "y"));
        REQUIRE(whileAdder.contains(9, "z"));
        REQUIRE(whileAdder.contains(9, "a"));
    }

    SECTION("While Pattern Negative") {
        REQUIRE_FALSE(whileAdder.contains(9, "1"));
        REQUIRE_FALSE(whileAdder.contains(5, "x"));
        REQUIRE_FALSE(whileAdder.contains(5, "y"));
    }

    SECTION("If Pattern Basic") {
        REQUIRE(ifAdder.contains(5, "x"));
        REQUIRE(ifAdder.contains(5, "y"));
    }

    SECTION("If Pattern Negative") {
        REQUIRE_FALSE(ifAdder.contains(5, "1"));
        REQUIRE_FALSE(ifAdder.contains(9, "x"));
        REQUIRE_FALSE(ifAdder.contains(9, "y"));
        REQUIRE_FALSE(ifAdder.contains(9, "z"));
        REQUIRE_FALSE(ifAdder.contains(9, "a"));
    }
}

TEST_CASE("Evaluate IfWhile Pattern - OK - Stub storage contains expected value") {

    filesystem::path filePath = filesystem::current_path().parent_path();
    string separator = string(1, filesystem::path::preferred_separator);
    string file = filePath.string() + separator + "integration_testing" +
        separator + "tests" + separator + "sp_ifwhile_pattern.txt";
    string src = FileReader::readFile(file);

    StubAssignPatternAdder assignAdder;
    StubIfPatternAdder ifAdder;
    StubWhilePatternAdder whileAdder;
    PatternExtractorVisitor extractor(assignAdder, ifAdder, whileAdder);
    Tokenizer tokenizer;
    SPParserManager parser;

    std::shared_ptr<RootNode> root = parser.parse(tokenizer.tokenize(src));
    
    extractor.begin(*root);
    extractor.transfer();

    SECTION("If Pattern long expressions") {
        REQUIRE(ifAdder.contains(1, "a"));
        REQUIRE(ifAdder.contains(1, "b"));
        REQUIRE(ifAdder.contains(1, "c"));
        REQUIRE(ifAdder.contains(1, "d"));
        REQUIRE(ifAdder.contains(1, "e"));
        REQUIRE(ifAdder.contains(1, "f"));
        REQUIRE(ifAdder.contains(1, "h"));
        REQUIRE(ifAdder.contains(6, "y"));
        REQUIRE(ifAdder.contains(6, "z"));
        REQUIRE(ifAdder.contains(12, "i"));
        REQUIRE(ifAdder.contains(12, "j"));
    }

    SECTION("If Pattern negative") {
        REQUIRE(ifAdder.size(1) == 7);
        REQUIRE(ifAdder.size(6) == 2);
        REQUIRE(ifAdder.size(12) == 2);
    }

    SECTION("While Pattern long expressions") {
        REQUIRE(whileAdder.contains(2, "i"));
        REQUIRE(whileAdder.contains(2, "j"));
        REQUIRE(whileAdder.contains(4, "k"));
        REQUIRE(whileAdder.contains(4, "l"));
        REQUIRE(whileAdder.contains(9, "q"));
        REQUIRE(whileAdder.contains(11, "a"));
        REQUIRE(whileAdder.contains(11, "b"));
        REQUIRE(whileAdder.contains(11, "c"));
        REQUIRE(whileAdder.contains(11, "d"));
        REQUIRE(whileAdder.contains(11, "e"));
        REQUIRE(whileAdder.contains(11, "f"));
        REQUIRE(whileAdder.contains(11, "h"));
        REQUIRE(whileAdder.contains(14, "k"));
        REQUIRE(whileAdder.contains(14, "l"));
    }

    SECTION("While Pattern long expressions") {
        REQUIRE(whileAdder.contains(2, "i"));
        REQUIRE(whileAdder.contains(2, "j"));
        REQUIRE(whileAdder.contains(4, "k"));
        REQUIRE(whileAdder.contains(4, "l"));
        REQUIRE(whileAdder.contains(9, "q"));
        REQUIRE(whileAdder.contains(11, "a"));
        REQUIRE(whileAdder.contains(11, "b"));
        REQUIRE(whileAdder.contains(11, "c"));
        REQUIRE(whileAdder.contains(11, "d"));
        REQUIRE(whileAdder.contains(11, "e"));
        REQUIRE(whileAdder.contains(11, "f"));
        REQUIRE(whileAdder.contains(11, "h"));
        REQUIRE(whileAdder.contains(14, "k"));
        REQUIRE(whileAdder.contains(14, "l"));
    }

    SECTION("While Pattern negative") {
        REQUIRE(whileAdder.size(2) == 2);
        REQUIRE(whileAdder.size(4) == 2);
        REQUIRE(whileAdder.size(9) == 1);
        REQUIRE(whileAdder.size(11) == 7);
        REQUIRE(whileAdder.size(14) == 2);
    }

    SECTION("Assign nested within containers") {
        REQUIRE(assignAdder.checkFullPattern(3, "k", "l + m"));
        REQUIRE(assignAdder.checkFullPattern(5, "n", "o + p"));
        REQUIRE(assignAdder.checkFullPattern(7, "w", "3"));
        REQUIRE(assignAdder.checkFullPattern(8, "v", "3"));
        REQUIRE(assignAdder.checkFullPattern(10, "r", "s + t"));
        REQUIRE(assignAdder.checkFullPattern(13, "k", "l + m"));
        REQUIRE(assignAdder.checkFullPattern(15, "n", "o + p"));
        REQUIRE(assignAdder.checkFullPattern(16, "r", "s + t"));
        REQUIRE(assignAdder.patternMap.size() == 8);
    }
}
