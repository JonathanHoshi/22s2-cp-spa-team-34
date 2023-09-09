//
// Created by Ryan Low on 5/2/23.
//
#include "catch.hpp"
#include "common/tokenizer/Tokenizer.h"
#include "qps/preprocessor/parser/ParserManager.h"
#include "qps/argument/entity/VariableEntity.h"

TEST_CASE("QPS Demo 1 Parser Tests") {
    SECTION(
        "Valid PQL query, ideal query"
        "procedure a; select b; stmt c;"
        "Select c"
    ) {
        std::vector<Token> tokens = {
            Token("procedure"), Token("a"),
            Token(";"), Token("variable"),
            Token("b"), Token(";"),
            Token("stmt"), Token("c"),
            Token(";"), Token("Select"), Token("a")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::OK);
        REQUIRE(aq.getSelectionList().size() == 1);
        REQUIRE(aq.getSelectionList()[0]->getValue() == "a");
    };
    SECTION(
        "Valid PQL query, weird caps"
        "variable a, b;"
        "Select a"
    ) {
        std::vector<Token> tokens = {
            Token("vaRiable"), Token("a"),
            Token(","), Token("b"),
            Token(";"), Token("SeLeCt"),
            Token("a")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        try {
            pm.parse(tokens, aq);
            FAIL("DECLARATION TYPE IS CASE SENSITIVE!");
        } catch (ParserError pe) {
            REQUIRE(pe.status() == ErrorStatus::SYNTAX);
        }
    };
    SECTION(
        "Valid PQL query, entity name is Select"
        "procedure Select, b;"
        "Select Select"
    ) {
        std::vector<Token> tokens = {
            Token("procedure"), Token("Select"),
            Token(","), Token("b"),
            Token(";"), Token("Select"),
            Token("Select")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::OK);
        REQUIRE(aq.getSelectionList().size() == 1);
        REQUIRE(aq.getSelectionList()[0]->getValue() == "Select");
    };
    SECTION(
        "Invalid PQL query, no comma separating variable names"
        "variable a b;"
        "Select a"
    ) {
        std::vector<Token> tokens = {
            Token("variable"), Token("a"), Token("b"),
            Token(";"), Token("Select"),
            Token("a")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        try {
            pm.parse(tokens, aq);
            FAIL("NO COMMA SEPARATING DECLARATION!");
        } catch (ParserError pe) {
            REQUIRE(pe.status() == ErrorStatus::SYNTAX);
        }
    };

    SECTION(
        "Invalid PQL query, re-declared variable"
        "variable a; variable a;"
        "Select a"
    ) {
        std::vector<Token> tokens = {
            Token("variable"), Token("a"), Token(";"), Token("variable"), Token("a"),
            Token(";"), Token("Select"),
            Token("a")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::SEMANTIC);
    };

    SECTION(
        "Invalid PQL query, semi colon after select clause"
        "variable a, b;"
        "Select a;"
    ) {
        std::vector<Token> tokens = {
            Token("variable"), Token("a"),
            Token(","), Token("b"),
            Token(";"), Token("Select"),
            Token("a"), Token(";")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        try {
            pm.parse(tokens, aq);
            FAIL("UNEXPECTED SEMICOLON AFTER SELECT!");
        } catch (ParserError pe) {
            REQUIRE(pe.status() == ErrorStatus::SYNTAX);
        }
    };
    SECTION(
        "Invalid PQL query, synonym not declared"
        "variable a, b;"
        "Select w;"
    ) {
        std::vector<Token> tokens = {
            Token("variable"), Token("a"),
            Token(","), Token("b"),
            Token(";"), Token("Select"),
            Token("w"), Token(";")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        try {
            pm.parse(tokens, aq);
            FAIL("UNDECLARED SYNONYM IN SELECT!");
        } catch (ParserError pe) {
            REQUIRE(pe.status() == ErrorStatus::SYNTAX);
        }
    };
}

TEST_CASE("QPS Modifies Parser Tests") {
    SECTION(
        "Valid PQL query, ideal query"
        "procedure a;"
        "Select a such that Modifies(a, \"x\")"
    ) {
        std::vector<Token> tokens = {
            IdentityToken("procedure"), IdentityToken("a"),
            PunctuationToken(";"), IdentityToken("Select"),
            IdentityToken("a"), IdentityToken("such"),
            IdentityToken("that"), IdentityToken("Modifies"),
            PunctuationToken("("), IdentityToken("a"),
            PunctuationToken(","), PunctuationToken("\""),
            IdentityToken("x"), PunctuationToken("\""),
            PunctuationToken(")")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::OK);
        REQUIRE(aq.getSelectionList().size() == 1);
        REQUIRE(aq.getSelectionList()[0]->getValue() == "a");
        REQUIRE(aq.getClauseList().size() == 1);
        REQUIRE(aq.getClauseList()[0].get()->getArgumentList()[0]->getValue() == "a");
        REQUIRE(aq.getClauseList()[0].get()->getArgumentList()[1]->getValue() == "x");
    };
    SECTION(
        "Valid PQL query, ideal query"
        "variable a;"
        "Select a such that Modifies(12, a)"
    ) {
        std::vector<Token> tokens = {
            IdentityToken("variable"), IdentityToken("a"),
            PunctuationToken(";"), IdentityToken("Select"),
            IdentityToken("a"), IdentityToken("such"),
            IdentityToken("that"), IdentityToken("Modifies"),
            PunctuationToken("("), NumberToken("12"),
            PunctuationToken(","), IdentityToken("a"),
            PunctuationToken(")")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::OK);
        REQUIRE(aq.getSelectionList().size() == 1);
        REQUIRE(aq.getSelectionList()[0]->getValue() == "a");
        REQUIRE(aq.getClauseList().size() == 1);
        REQUIRE(aq.getClauseList()[0].get()->getArgumentList()[0]->getValue() == "12");
        REQUIRE(aq.getClauseList()[0].get()->getArgumentList()[1]->getValue() == "a");
    };

    SECTION(
        "Valid PQL query, ideal query"
        "variable a;"
        "Select a such that Modifies(\"main\", a)"
    ) {
        std::vector<Token> tokens = {
            IdentityToken("variable"), IdentityToken("a"),
            PunctuationToken(";"), IdentityToken("Select"),
            IdentityToken("a"), IdentityToken("such"),
            IdentityToken("that"), IdentityToken("Modifies"),
            PunctuationToken("("), PunctuationToken("\""),
            IdentityToken("main"), PunctuationToken("\""),
            PunctuationToken(","), IdentityToken("a"),
            PunctuationToken(")")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::OK);
        REQUIRE(aq.getSelectionList().size() == 1);
        REQUIRE(aq.getSelectionList()[0]->getValue() == "a");
        REQUIRE(aq.getClauseList().size() == 1);
        REQUIRE(aq.getClauseList()[0].get()->getArgumentList()[0]->getValue() == "main");
        REQUIRE(aq.getClauseList()[0].get()->getArgumentList()[1]->getValue() == "a");
    };

    SECTION(
        "Valid PQL query, ideal query"
        "variable a;"
        "Select a such that Modifies(\"main\", _)"
    ) {
        std::vector<Token> tokens = {
            IdentityToken("variable"), IdentityToken("a"),
            PunctuationToken(";"), IdentityToken("Select"),
            IdentityToken("a"), IdentityToken("such"),
            IdentityToken("that"), IdentityToken("Modifies"),
            PunctuationToken("("), PunctuationToken("\""),
            IdentityToken("main"), PunctuationToken("\""),
            PunctuationToken(","), PunctuationToken("_"),
            PunctuationToken(")")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::OK);
        REQUIRE(aq.getSelectionList().size() == 1);
        REQUIRE(aq.getSelectionList()[0]->getValue() == "a");
        REQUIRE(aq.getClauseList().size() == 1);
        REQUIRE(aq.getClauseList()[0].get()->getArgumentList()[0]->getValue() == "main");
        REQUIRE(WildcardEntity::checkInstance(aq.getClauseList()[0].get()->getArgumentList()[1].get()));
    };
    SECTION(
        "Valid PQL query, ideal query"
        "variable a, b; "
        "Select a such that Modifies(a, b)"
    ) {
        std::vector<Token> tokens = {
            IdentityToken("variable"), IdentityToken("a"), PunctuationToken(","),
            IdentityToken("b"), PunctuationToken(";"), IdentityToken("Select"),
            IdentityToken("a"), IdentityToken("such"),
            IdentityToken("that"), IdentityToken("Modifies"),
            PunctuationToken("("), IdentityToken("a"),
            PunctuationToken(","), IdentityToken("b"),
            PunctuationToken(")")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::SEMANTIC);
    };
}

TEST_CASE("QPS Uses Parser Tests") {
    SECTION(
        "Valid PQL query, ideal query"
        "procedure a;"
        "Select a such that Uses(a, \"x\")"
    ) {
        std::vector<Token> tokens = {
            IdentityToken("procedure"), IdentityToken("a"),
            PunctuationToken(";"), IdentityToken("Select"),
            IdentityToken("a"), IdentityToken("such"),
            IdentityToken("that"), IdentityToken("Uses"),
            PunctuationToken("("), IdentityToken("a"),
            PunctuationToken(","), PunctuationToken("\""),
            IdentityToken("x"), PunctuationToken("\""),
            PunctuationToken(")")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::OK);
        REQUIRE(aq.getSelectionList().size() == 1);
        REQUIRE(aq.getSelectionList()[0]->getValue() == "a");
        REQUIRE(aq.getClauseList().size() == 1);
        REQUIRE(aq.getClauseList()[0].get()->getArgumentList()[0]->getValue() == "a");
        REQUIRE(aq.getClauseList()[0].get()->getArgumentList()[1]->getValue() == "x");
    };
    SECTION(
        "Valid PQL query, ideal query"
        "variable a;"
        "Select a such that Uses(12, a)"
    ) {
        std::vector<Token> tokens = {
            IdentityToken("variable"), IdentityToken("a"),
            PunctuationToken(";"), IdentityToken("Select"),
            IdentityToken("a"), IdentityToken("such"),
            IdentityToken("that"), IdentityToken("Uses"),
            PunctuationToken("("), NumberToken("12"),
            PunctuationToken(","), IdentityToken("a"),
            PunctuationToken(")")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::OK);
        REQUIRE(aq.getSelectionList().size() == 1);
        REQUIRE(aq.getSelectionList()[0]->getValue() == "a");
        REQUIRE(aq.getClauseList().size() == 1);
        REQUIRE(aq.getClauseList()[0].get()->getArgumentList()[0]->getValue() == "12");
        REQUIRE(aq.getClauseList()[0].get()->getArgumentList()[1]->getValue() == "a");
    };

    SECTION(
        "Valid PQL query, ideal query"
        "variable a;"
        "Select a such that Uses(\"main\", a)"
    ) {
        std::vector<Token> tokens = {
            IdentityToken("variable"), IdentityToken("a"),
            PunctuationToken(";"), IdentityToken("Select"),
            IdentityToken("a"), IdentityToken("such"),
            IdentityToken("that"), IdentityToken("Uses"),
            PunctuationToken("("), PunctuationToken("\""),
            IdentityToken("main"), PunctuationToken("\""),
            PunctuationToken(","), IdentityToken("a"),
            PunctuationToken(")")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::OK);
        REQUIRE(aq.getSelectionList().size() == 1);
        REQUIRE(aq.getSelectionList()[0]->getValue() == "a");
        REQUIRE(aq.getClauseList().size() == 1);
        REQUIRE(aq.getClauseList()[0].get()->getArgumentList()[0]->getValue() == "main");
        REQUIRE(aq.getClauseList()[0].get()->getArgumentList()[1]->getValue() == "a");
    };
}

TEST_CASE("QPS Parent Follows Parser Tests") {
    SECTION(
        "Valid PQL query, ideal query"
        "procedure a;"
        "Select a such that Parent(1, 2)"
    ) {
        std::vector<Token> tokens = {
            IdentityToken("procedure"), IdentityToken("a"),
            PunctuationToken(";"), IdentityToken("Select"),
            IdentityToken("a"), IdentityToken("such"),
            IdentityToken("that"), IdentityToken("Parent"),
            PunctuationToken("("), NumberToken("1"),
            PunctuationToken(","), NumberToken("2"),
            PunctuationToken(")")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::OK);
        REQUIRE(aq.getSelectionList().size() == 1);
        REQUIRE(aq.getSelectionList()[0]->getValue() == "a");
        REQUIRE(aq.getClauseList().size() == 1);
        std::string test = aq.getClauseList()[0].get()->getArgumentList()[0]->getValue();
        std::string test2 = aq.getClauseList()[0].get()->getArgumentList()[1]->getValue();
        REQUIRE(test == "1");
        REQUIRE(test2 == "2");
    };
    SECTION(
        "Valid PQL query, ideal query"
        "variable a;"
        "Select a such that Parent(12, a)"
    ) {
        std::vector<Token> tokens = {
            IdentityToken("variable"), IdentityToken("a"),
            PunctuationToken(";"), IdentityToken("Select"),
            IdentityToken("a"), IdentityToken("such"),
            IdentityToken("that"), IdentityToken("Parent"),
            PunctuationToken("("), NumberToken("12"),
            PunctuationToken(","), NumberToken("1"),
            PunctuationToken(")")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::OK);
        REQUIRE(aq.getSelectionList().size() == 1);
        REQUIRE(aq.getSelectionList()[0]->getValue() == "a");
        REQUIRE(aq.getClauseList().size() == 1);
        REQUIRE(aq.getClauseList()[0].get()->getArgumentList()[0]->getValue() == "12");
        REQUIRE(aq.getClauseList()[0].get()->getArgumentList()[1]->getValue() == "1");
    };

    SECTION(
        "Invalid PQL query"
        "stmt a;"
        "Select a such that Follows(\"main\", a)"
    ) {
        std::vector<Token> tokens = {
            IdentityToken("stmt"), IdentityToken("a"),
            PunctuationToken(";"), IdentityToken("Select"),
            IdentityToken("a"), IdentityToken("such"),
            IdentityToken("that"), IdentityToken("Follows"),
            PunctuationToken("("), PunctuationToken("\""),
            IdentityToken("main"), PunctuationToken("\""),
            PunctuationToken(","), IdentityToken("a"),
            PunctuationToken(")")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        try {
            pm.parse(tokens, aq);
            FAIL("Non-statement passed in as argument!");
        } catch (ParserError pe) {
            REQUIRE(pe.status() == ErrorStatus::SYNTAX);
        }
    };

    SECTION(
        "Invalid PQL query"
        "stmt a;"
        "Select a such that Follows*(\"x\", 2)"
    ) {
        std::vector<Token> tokens = {
            IdentityToken("stmt"), IdentityToken("a"),
            PunctuationToken(";"), IdentityToken("Select"),
            IdentityToken("a"), IdentityToken("such"),
            IdentityToken("that"), IdentityToken("Follows"),
            PunctuationToken("*"), PunctuationToken("("),
            PunctuationToken("\""), IdentityToken("x"),
            PunctuationToken("\""), PunctuationToken(","),
            NumberToken("2"), PunctuationToken(")")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        try {
            pm.parse(tokens, aq);
            FAIL("Non-statement passed in as argument!");
        } catch (ParserError pe) {
            REQUIRE(pe.status() == ErrorStatus::SYNTAX);
        }
    };

    SECTION(
        "Valid PQL query, ideal query"
        "stmt a; procedure p;"
        "Select a such that Parent(p, a)"
    ) {
        std::vector<Token> tokens = {
            IdentityToken("stmt"), IdentityToken("a"),
            PunctuationToken(";"), IdentityToken("procedure"), IdentityToken("p"),
            PunctuationToken(";"), IdentityToken("Select"),
            IdentityToken("a"), IdentityToken("such"),
            IdentityToken("that"), IdentityToken("Parent"),
            PunctuationToken("("), IdentityToken("p"),
            PunctuationToken(","), IdentityToken("a"),
            PunctuationToken(")")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::SEMANTIC);
    };

    SECTION(
        "Valid PQL query, ideal query"
        "while a; if ifs;"
        "Select a such that Parent(a, ifs)"
    ) {
        std::vector<Token> tokens = {
            IdentityToken("while"), IdentityToken("a"),
            PunctuationToken(";"), IdentityToken("if"), IdentityToken("ifs"),
            PunctuationToken(";"), IdentityToken("Select"),
            IdentityToken("a"), IdentityToken("such"),
            IdentityToken("that"), IdentityToken("Parent"),
            PunctuationToken("("), IdentityToken("a"),
            PunctuationToken(","), IdentityToken("ifs"),
            PunctuationToken(")")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::OK);
        REQUIRE(aq.getSelectionList().size() == 1);
        REQUIRE(aq.getSelectionList()[0]->getValue() == "a");
        REQUIRE(aq.getClauseList().size() == 1);
        REQUIRE(aq.getClauseList()[0].get()->getArgumentList()[0]->getValue() == "a");
        REQUIRE(aq.getClauseList()[0].get()->getArgumentList()[1]->getValue() == "ifs");
    };

    SECTION(
        "Valid PQL query, ideal query"
        "while a; if ifs;"
        "Select a such that Parent(a, _)"
    ) {
        std::vector<Token> tokens = {
            IdentityToken("while"), IdentityToken("a"),
            PunctuationToken(";"), IdentityToken("if"), IdentityToken("ifs"),
            PunctuationToken(";"), IdentityToken("Select"),
            IdentityToken("a"), IdentityToken("such"),
            IdentityToken("that"), IdentityToken("Parent"),
            PunctuationToken("*"),
            PunctuationToken("("), IdentityToken("a"),
            PunctuationToken(","), PunctuationToken("_"),
            PunctuationToken(")")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::OK);
        REQUIRE(aq.getSelectionList().size() == 1);
        REQUIRE(aq.getSelectionList()[0]->getValue() == "a");
        REQUIRE(aq.getClauseList().size() == 1);
        REQUIRE(aq.getClauseList()[0].get()->getArgumentList()[0]->getValue() == "a");
        REQUIRE(WildcardEntity::checkInstance(aq.getClauseList()[0].get()->getArgumentList()[1].get()));
    };
}

TEST_CASE("QPS assign pattern Parser Tests") {
    SECTION(
        "Valid PQL query, ideal query"
        "assign a;"
        "Select a pattern a(\"x\", \"x + y\")"
    ) {
        std::vector<Token> tokens = {
            IdentityToken("assign"), IdentityToken("a"),
            PunctuationToken(";"), IdentityToken("Select"),
            IdentityToken("a"), IdentityToken("pattern"),
            IdentityToken("a"), PunctuationToken("("),
            PunctuationToken("\""), IdentityToken("x"),
            PunctuationToken("\""), PunctuationToken(","),
            PunctuationToken("\""), IdentityToken("x"),
            PunctuationToken("+"), IdentityToken("y"),
            PunctuationToken("\""), PunctuationToken(")")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::OK);
        REQUIRE(aq.getSelectionList().size() == 1);
        REQUIRE(aq.getSelectionList()[0]->getValue() == "a");
        REQUIRE(aq.getClauseList().size() == 1);
        std::string test = aq.getClauseList()[0].get()->getArgumentList()[1]->getValue();
        std::string test2 = aq.getClauseList()[0].get()->getArgumentList()[2]->getValue();
        REQUIRE(test == "x");
        REQUIRE(test2 == "x+y");
    };
    SECTION(
        "Valid PQL query, ideal query"
        "assign a; variable v;"
        "Select a pattern a(v, _\"x + y\"_)"
    ) {
        std::vector<Token> tokens = {
            IdentityToken("assign"), IdentityToken("a"),
            PunctuationToken(";"), IdentityToken("variable"),
            IdentityToken("v"), PunctuationToken(";"), IdentityToken("Select"),
            IdentityToken("a"), IdentityToken("pattern"),
            IdentityToken("a"), PunctuationToken("("),
            IdentityToken("v"), PunctuationToken(","),
            PunctuationToken("_"), PunctuationToken("\""), IdentityToken("x"),
            PunctuationToken("+"), IdentityToken("y"),
            PunctuationToken("\""), PunctuationToken("_"), PunctuationToken(")")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::OK);
        REQUIRE(aq.getSelectionList().size() == 1);
        REQUIRE(aq.getSelectionList()[0]->getValue() == "a");
        REQUIRE(aq.getClauseList().size() == 1);
        std::string test = aq.getClauseList()[0].get()->getArgumentList()[1]->getValue();
        std::string test2 = aq.getClauseList()[0].get()->getArgumentList()[2]->getValue();
        REQUIRE(test == "v");
        REQUIRE(test2 == "x+y");
    };
    SECTION(
        "Valid PQL query, ideal query"
        "assign a; variable v;"
        "Select a pattern a(v, _\"ryan\"_)"
    ) {
        std::vector<Token> tokens = {
            IdentityToken("assign"), IdentityToken("a"),
            PunctuationToken(";"), IdentityToken("variable"),
            IdentityToken("v"), PunctuationToken(";"), IdentityToken("Select"),
            IdentityToken("a"), IdentityToken("pattern"),
            IdentityToken("a"), PunctuationToken("("),
            IdentityToken("v"), PunctuationToken(","),
            PunctuationToken("_"), PunctuationToken("\""), IdentityToken("ryan"),
            PunctuationToken("\""), PunctuationToken("_"), PunctuationToken(")")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::OK);
        REQUIRE(aq.getSelectionList().size() == 1);
        REQUIRE(aq.getSelectionList()[0]->getValue() == "a");
        REQUIRE(aq.getClauseList().size() == 1);
        std::string test = aq.getClauseList()[0].get()->getArgumentList()[1]->getValue();
        std::string test2 = aq.getClauseList()[0].get()->getArgumentList()[2]->getValue();
        REQUIRE(test == "v");
        REQUIRE(test2 == "ryan");
    };
    SECTION(
        "Valid PQL query, ideal query"
        "assign a; variable v;"
        "Select v pattern a(v, _\"(x + y)\"_)"
    ) {
        std::vector<Token> tokens = {
            IdentityToken("assign"), IdentityToken("a"),
            PunctuationToken(";"), IdentityToken("variable"),
            IdentityToken("v"), PunctuationToken(";"), IdentityToken("Select"),
            IdentityToken("a"), IdentityToken("pattern"),
            IdentityToken("a"), PunctuationToken("("),
            IdentityToken("v"), PunctuationToken(","),
            PunctuationToken("_"), PunctuationToken("\""), PunctuationToken("("), PunctuationToken("("), IdentityToken("x"),
            PunctuationToken("+"), IdentityToken("y"), PunctuationToken(")"), PunctuationToken(")"),
            PunctuationToken("\""), PunctuationToken("_"), PunctuationToken(")")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::OK);
        REQUIRE(aq.getSelectionList().size() == 1);
        REQUIRE(aq.getSelectionList()[0]->getValue() == "a");
        REQUIRE(aq.getClauseList().size() == 1);
        std::string test = aq.getClauseList()[0].get()->getArgumentList()[0]->getValue();
        std::string test2 = aq.getClauseList()[0].get()->getArgumentList()[1]->getValue();
        std::string test3 = aq.getClauseList()[0].get()->getArgumentList()[2]->getValue();
        REQUIRE(test == "a");
        REQUIRE(test2 == "v");
        REQUIRE(test3 == "((x+y))");
    };
    SECTION(
        "Invalid PQL query, space between numbers"
        "assign a; variable v;"
        "Select v pattern a(v, _\"(x + 6 9)\"_)"
    ) {
        std::vector<Token> tokens = {
            IdentityToken("assign"), IdentityToken("a"),
            PunctuationToken(";"), IdentityToken("variable"),
            IdentityToken("v"), PunctuationToken(";"), IdentityToken("Select"),
            IdentityToken("a"), IdentityToken("pattern"),
            IdentityToken("a"), PunctuationToken("("),
            IdentityToken("v"), PunctuationToken(","),
            PunctuationToken("_"), PunctuationToken("\""), PunctuationToken("("), IdentityToken("x"),
            PunctuationToken("+"), NumberToken("6"), NumberToken("9"), PunctuationToken(")"),
            PunctuationToken("\""), PunctuationToken("_"), PunctuationToken(")")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        try {
            pm.parse(tokens, aq);
            FAIL("UNEXPECTED SPACE BETWEEN NUMBERS!");
        } catch (ParserError pe) {
            REQUIRE(pe.status() == ErrorStatus::SYNTAX);
        }
    };
    SECTION(
        "Invalid PQL query, space between numbers"
        "assign a; variable v;"
        "Select v pattern a(v, _\"x + 6 9\"_)"
    ) {
        std::vector<Token> tokens = {
            IdentityToken("assign"), IdentityToken("a"),
            PunctuationToken(";"), IdentityToken("variable"),
            IdentityToken("v"), PunctuationToken(";"), IdentityToken("Select"),
            IdentityToken("a"), IdentityToken("pattern"),
            IdentityToken("a"), PunctuationToken("("),
            IdentityToken("v"), PunctuationToken(","),
            PunctuationToken("_"), PunctuationToken("\""), IdentityToken("x"),
            PunctuationToken("+"), NumberToken("6"), NumberToken("9"),
            PunctuationToken("\""), PunctuationToken("_"), PunctuationToken(")")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        try {
            pm.parse(tokens, aq);
            FAIL("UNEXPECTED SPACE BETWEEN NUMBERS!");
        } catch (ParserError pe) {
            REQUIRE(pe.status() == ErrorStatus::SYNTAX);
        }
    };
}

TEST_CASE("QPS Milestone 2 Parser Tests") {
    SECTION(
        "Valid PQL query, ideal query"
        "assign a; variable v; Select v pattern a(v, _\"(1 + (x + y))\"_) such that Uses (a, v)"
    ) {
        std::vector<Token> tokens = {
            IdentityToken("assign"), IdentityToken("a"),
            PunctuationToken(";"), IdentityToken("variable"),
            IdentityToken("v"), PunctuationToken(";"), IdentityToken("Select"),
            IdentityToken("v"), IdentityToken("pattern"),
            IdentityToken("a"), PunctuationToken("("), IdentityToken("v"),
            PunctuationToken(","), PunctuationToken("_"), PunctuationToken("\""), PunctuationToken("("),
            NumberToken("1"), PunctuationToken("+"), PunctuationToken("("),
            IdentityToken("x"), PunctuationToken("+"), IdentityToken("y"), PunctuationToken(")"),
            PunctuationToken(")"),
            PunctuationToken("\""), PunctuationToken("_"), PunctuationToken(")"), IdentityToken("such"),
            IdentityToken("that"), IdentityToken("Uses"),
            PunctuationToken("("), IdentityToken("a"),
            PunctuationToken(","), IdentityToken("v"),
            PunctuationToken(")")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::OK);
        REQUIRE(aq.getSelectionList().size() == 1);
        REQUIRE(aq.getSelectionList()[0]->getValue() == "v");
        REQUIRE(aq.getClauseList().size() == 2);
        std::string test = aq.getClauseList()[0].get()->getArgumentList()[0]->getValue();
        std::string test1 = aq.getClauseList()[0].get()->getArgumentList()[1]->getValue();
        std::string test2 = aq.getClauseList()[0].get()->getArgumentList()[2]->getValue();
        REQUIRE(test == "a");
        REQUIRE(test1 == "v");
        REQUIRE(test2 == "(1+(x+y))");
        std::string test3 = aq.getClauseList()[1].get()->getArgumentList()[0]->getValue();
        std::string test4 = aq.getClauseList()[1].get()->getArgumentList()[1]->getValue();
        REQUIRE(test3 == "a");
        REQUIRE(test4 == "v");
    };
    SECTION(
        "Valid PQL query, ideal query"
        "assign a; variable v; Select v such that Uses(a, v) such that Follows(a, 2)"
    ) {
        std::vector<Token> tokens = {
            IdentityToken("assign"), IdentityToken("a"),
            PunctuationToken(";"), IdentityToken("variable"),
            IdentityToken("v"), PunctuationToken(";"), IdentityToken("Select"),
            IdentityToken("v"), IdentityToken("such"),
            IdentityToken("that"), IdentityToken("Uses"),
            PunctuationToken("("), IdentityToken("a"),
            PunctuationToken(","), IdentityToken("v"),
            PunctuationToken(")"), IdentityToken("such"),
            IdentityToken("that"), IdentityToken("Follows"),
            PunctuationToken("("), IdentityToken("a"),
            PunctuationToken(","), NumberToken("2"),
            PunctuationToken(")")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::OK);
        REQUIRE(aq.getSelectionList().size() == 1);
        REQUIRE(aq.getSelectionList()[0]->getValue() == "v");
        REQUIRE(aq.getClauseList().size() == 2);
        std::string test = aq.getClauseList()[0].get()->getArgumentList()[0]->getValue();
        std::string test2 = aq.getClauseList()[0].get()->getArgumentList()[1]->getValue();
        REQUIRE(test == "a");
        REQUIRE(test2 == "v");
        std::string test3 = aq.getClauseList()[1].get()->getArgumentList()[0]->getValue();
        std::string test4 = aq.getClauseList()[1].get()->getArgumentList()[1]->getValue();
        REQUIRE(test3 == "a");
        REQUIRE(test4 == "2");
    };

    SECTION(
        "assign a1, a2; while w; "
        "Select a2 such that Parent*(w, a1) pattern w(_, _) such that Modifies(a1, \"east\") such that Uses(a1, \"west\") such that Follows*(a1, a2)"
    ) {
        std::vector<Token> tokens = {
            IdentityToken("assign"), IdentityToken("a1"),
            PunctuationToken(","), IdentityToken("a2"),
            PunctuationToken(";"), IdentityToken("while"), IdentityToken("w"),
            PunctuationToken(";"), IdentityToken("Select"),
            IdentityToken("a2"), IdentityToken("such"),
            IdentityToken("that"), IdentityToken("Parent"), PunctuationToken("*"),
            PunctuationToken("("), IdentityToken("w"),
            PunctuationToken(","), IdentityToken("a1"),
            PunctuationToken(")"), IdentityToken("pattern"),
            IdentityToken("w"), PunctuationToken("("), PunctuationToken("_"),
            PunctuationToken(","), PunctuationToken("_"),
            PunctuationToken(")"), IdentityToken("such"),
            IdentityToken("that"), IdentityToken("Modifies"),
            PunctuationToken("("), IdentityToken("a1"),
            PunctuationToken(","), PunctuationToken("\""),
            IdentityToken("east"), PunctuationToken("\""),
            PunctuationToken(")"), IdentityToken("such"),
            IdentityToken("that"), IdentityToken("Uses"),
            PunctuationToken("("), IdentityToken("a1"),
            PunctuationToken(","), PunctuationToken("\""),
            IdentityToken("west"), PunctuationToken("\""),
            PunctuationToken(")"), IdentityToken("such"),
            IdentityToken("that"), IdentityToken("Follows"), PunctuationToken("*"),
            PunctuationToken("("), IdentityToken("a1"),
            PunctuationToken(","), IdentityToken("a2"),
            PunctuationToken(")")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::OK);
        REQUIRE(aq.getSelectionList().size() == 1);
        REQUIRE(aq.getSelectionList()[0]->getValue() == "a2");
        REQUIRE(aq.getClauseList().size() == 5);
        std::string test = aq.getClauseList()[1].get()->getArgumentList()[0]->getValue();
        std::string test2 = aq.getClauseList()[1].get()->getArgumentList()[1]->getValue();
        REQUIRE(test == "w");
        REQUIRE(test2 == "");
    };
}

TEST_CASE("QPS Select Boolean Tests") {
    SECTION(
        "Valid PQL query"
        "Select BOOLEAN such that Parent(12, 10)"
    ) {
        std::vector<Token> tokens = {
            IdentityToken("Select"),
            IdentityToken("BOOLEAN"), IdentityToken("such"),
            IdentityToken("that"), IdentityToken("Parent"),
            PunctuationToken("("), NumberToken("12"),
            PunctuationToken(","), NumberToken("10"),
            PunctuationToken(")")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::OK);
        REQUIRE(aq.isSelectionEmpty());
        REQUIRE(aq.getSelectBoolean());
        REQUIRE(aq.getClauseList().size() == 1);
        REQUIRE(aq.getClauseList()[0].get()->getArgumentList()[0]->getValue() == "12");
        REQUIRE(aq.getClauseList()[0].get()->getArgumentList()[1]->getValue() == "10");
    };
    SECTION(
        "Invalid PQL query"
        "variable a;"
        "Select boOlEAN such that Uses(12, a)"
    ) {
        std::vector<Token> tokens = {
            IdentityToken("variable"), IdentityToken("a"),
            PunctuationToken(";"), IdentityToken("Select"),
            IdentityToken("bOOlEAN"), IdentityToken("such"),
            IdentityToken("that"), IdentityToken("Uses"),
            PunctuationToken("("), NumberToken("12"),
            PunctuationToken(","), IdentityToken("a"),
            PunctuationToken(")")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::SEMANTIC);
    };
    SECTION(
        "Valid PQL query, ideal query"
        "variable a;"
        "Select BOOLEAN such that Uses(12, a)"
    ) {
        std::vector<Token> tokens = {
            IdentityToken("variable"), IdentityToken("a"),
            PunctuationToken(";"), IdentityToken("Select"),
            IdentityToken("BOOLEAN"), IdentityToken("such"),
            IdentityToken("that"), IdentityToken("Uses"),
            PunctuationToken("("), NumberToken("12"),
            PunctuationToken(","), IdentityToken("a"),
            PunctuationToken(")")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::OK);
        REQUIRE(aq.isSelectionEmpty());
        REQUIRE(aq.getSelectBoolean());
        REQUIRE(aq.getClauseList().size() == 1);
        REQUIRE(aq.getClauseList()[0].get()->getArgumentList()[0]->getValue() == "12");
        REQUIRE(aq.getClauseList()[0].get()->getArgumentList()[1]->getValue() == "a");
    };

    SECTION(
        "Valid PQL query, ideal query"
        "while a; if ifs;"
        "Select BOOLEAN such that Parent(a, _)"
    ) {
        std::vector<Token> tokens = {
            IdentityToken("while"), IdentityToken("a"),
            PunctuationToken(";"), IdentityToken("if"), IdentityToken("ifs"),
            PunctuationToken(";"), IdentityToken("Select"),
            IdentityToken("BOOLEAN"), IdentityToken("such"),
            IdentityToken("that"), IdentityToken("Parent"),
            PunctuationToken("*"),
            PunctuationToken("("), IdentityToken("a"),
            PunctuationToken(","), PunctuationToken("_"),
            PunctuationToken(")")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::OK);
        REQUIRE(aq.isSelectionEmpty());
        REQUIRE(aq.getSelectBoolean());
        REQUIRE(aq.getClauseList().size() == 1);
        REQUIRE(aq.getClauseList()[0].get()->getArgumentList()[0]->getValue() == "a");
        REQUIRE(WildcardEntity::checkInstance(aq.getClauseList()[0].get()->getArgumentList()[1].get()));
    };
    SECTION(
        "Valid PQL query, ideal query"
        "assign a; variable v; Select BOOLEAN pattern a(v, _\"(1 + (x + y))\"_) such that Uses (a, v)"
    ) {
        std::vector<Token> tokens = {
            IdentityToken("assign"), IdentityToken("a"),
            PunctuationToken(";"), IdentityToken("variable"),
            IdentityToken("v"), PunctuationToken(";"), IdentityToken("Select"),
            IdentityToken("BOOLEAN"), IdentityToken("pattern"),
            IdentityToken("a"), PunctuationToken("("), IdentityToken("v"),
            PunctuationToken(","), PunctuationToken("_"), PunctuationToken("\""), PunctuationToken("("),
            NumberToken("1"), PunctuationToken("+"), PunctuationToken("("),
            IdentityToken("x"), PunctuationToken("+"), IdentityToken("y"), PunctuationToken(")"),
            PunctuationToken(")"),
            PunctuationToken("\""), PunctuationToken("_"), PunctuationToken(")"), IdentityToken("such"),
            IdentityToken("that"), IdentityToken("Uses"),
            PunctuationToken("("), IdentityToken("a"),
            PunctuationToken(","), IdentityToken("v"),
            PunctuationToken(")")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::OK);
        REQUIRE(aq.getSelectionList().size() == 0);
        REQUIRE(aq.getSelectBoolean());
        REQUIRE(aq.getClauseList().size() == 2);
        std::string test = aq.getClauseList()[0].get()->getArgumentList()[0]->getValue();
        std::string test1 = aq.getClauseList()[0].get()->getArgumentList()[1]->getValue();
        std::string test2 = aq.getClauseList()[0].get()->getArgumentList()[2]->getValue();
        REQUIRE(test == "a");
        REQUIRE(test1 == "v");
        REQUIRE(test2 == "(1+(x+y))");
        std::string test3 = aq.getClauseList()[1].get()->getArgumentList()[0]->getValue();
        std::string test4 = aq.getClauseList()[1].get()->getArgumentList()[1]->getValue();
        REQUIRE(test3 == "a");
        REQUIRE(test4 == "v");
    };
    SECTION(
        "Valid PQL query, entity name is Select"
        "procedure BOOLEAN, b;"
        "Select BOOLEAN"
    ) {
        std::vector<Token> tokens = {
            Token("procedure"), Token("BOOLEAN"),
            Token(","), Token("b"),
            Token(";"), Token("Select"),
            Token("BOOLEAN")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::OK);
        REQUIRE(!aq.getSelectBoolean());
        REQUIRE(aq.getSelectionList().size() == 1);
        REQUIRE(aq.getSelectionList()[0]->getValue() == "BOOLEAN");
    };

}

TEST_CASE("QPS Select tuple Tests") {
    SECTION(
        "Valid PQL query, ideal query"
        "procedure a; variable b; stmt c;"
        "Select <a, b>"
    ) {
        std::vector<Token> tokens = {
            Token("procedure"), Token("a"),
            Token(";"), Token("variable"),
            Token("b"), Token(";"),
            Token("stmt"), Token("c"),
            Token(";"), Token("Select"), Token("<"),
            Token("a"), Token(","), Token("b"), Token(">")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::OK);
        REQUIRE(aq.getSelectionList().size() == 2);
        REQUIRE(aq.getSelectionList()[0]->getValue() == "a");
        REQUIRE(aq.getSelectionList()[1]->getValue() == "b");
    };

    SECTION(
        "Valid PQL query, entity name is Select"
        "procedure BOOLEAN, b;"
        "Select <BOOLEAN, b>"
    ) {
        std::vector<Token> tokens = {
            Token("procedure"), Token("BOOLEAN"),
            Token(","), Token("b"),
            Token(";"), Token("Select"), Token("<"),
            Token("BOOLEAN"), Token(","), Token("b"), Token(">")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::OK);
        REQUIRE(aq.getSelectionList().size() == 2);
        REQUIRE(aq.getSelectionList()[0]->getValue() == "BOOLEAN");
        REQUIRE(aq.getSelectionList()[1]->getValue() == "b");

    };
    SECTION(
        "Invalid PQL query, no comma separating variable names"
        "variable a, b;"
        "Select <a b>"
    ) {
        std::vector<Token> tokens = {
            Token("variable"), Token("a"), Token(","), Token("b"),
            Token(";"), Token("Select"), Token("<"),
            Token("a"), Token("b"), Token(">")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        try {
            pm.parse(tokens, aq);
            FAIL("NO COMMA SEPARATING TUPLE!");
        } catch (ParserError pe) {
            REQUIRE(pe.status() == ErrorStatus::SYNTAX);
        }
    };

    SECTION(
        "Invalid PQL query, undeclared variable"
        "variable a; variable b;"
        "Select <a, c, b>"
    ) {
        std::vector<Token> tokens = {
            Token("variable"), Token("a"), Token(";"), Token("variable"), Token("b"),
            Token(";"), Token("Select"), Token("<"),
            Token("a"), Token(","), Token("c"), Token(","), Token("b"), Token(">")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::SEMANTIC);
    };

    SECTION(
        "Invalid PQL query, synonym not declared"
        "variable a, b;"
        "Select <a, b"
    ) {
        std::vector<Token> tokens = {
            Token("variable"), Token("a"),
            Token(","), Token("b"),
            Token(";"), Token("Select"), Token("<"),
            Token("a"), Token(","), Token("b")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        try {
            pm.parse(tokens, aq);
            FAIL("No closing tuple bracket!");
        } catch (ParserError pe) {
            REQUIRE(pe.status() == ErrorStatus::SYNTAX);
        }
    };
}

TEST_CASE("QPS Calls Parser Tests") {
    SECTION(
        "Valid PQL query, ideal query"
        "assign a;"
        "Select a such that Calls(\"x\", \"yyy\")"
    ) {
        std::vector<Token> tokens = {
            IdentityToken("assign"), IdentityToken("a"),
            PunctuationToken(";"), IdentityToken("Select"),
            IdentityToken("a"), IdentityToken("such"),
            IdentityToken("that"), IdentityToken("Calls"), PunctuationToken("("),
            PunctuationToken("\""), IdentityToken("x"),
            PunctuationToken("\""), PunctuationToken(","),
            PunctuationToken("\""), IdentityToken("yyy"),
            PunctuationToken("\""), PunctuationToken(")")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::OK);
        REQUIRE(aq.getSelectionList().size() == 1);
        REQUIRE(aq.getSelectionList()[0]->getValue() == "a");
        REQUIRE(aq.getClauseList().size() == 1);
        std::string test = aq.getClauseList()[0].get()->getArgumentList()[0]->getValue();
        std::string test2 = aq.getClauseList()[0].get()->getArgumentList()[1]->getValue();
        REQUIRE(test == "x");
        REQUIRE(test2 == "yyy");
    };

    SECTION(
        "Valid PQL query, ideal query"
        "procedure a, b;"
        "Select a such that Calls(a, b)"
    ) {
        std::vector<Token> tokens = {
            IdentityToken("procedure"), IdentityToken("a"), PunctuationToken(","), IdentityToken("b"),
            PunctuationToken(";"), IdentityToken("Select"),
            IdentityToken("a"), IdentityToken("such"),
            IdentityToken("that"), IdentityToken("Calls"),
            PunctuationToken("("), IdentityToken("a"),
            PunctuationToken(","), IdentityToken("b"),
            PunctuationToken(")")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::OK);
        REQUIRE(aq.getSelectionList().size() == 1);
        REQUIRE(aq.getSelectionList()[0]->getValue() == "a");
        REQUIRE(aq.getClauseList().size() == 1);
        std::string test = aq.getClauseList()[0].get()->getArgumentList()[0]->getValue();
        std::string test2 = aq.getClauseList()[0].get()->getArgumentList()[1]->getValue();
        REQUIRE(test == "a");
        REQUIRE(test2 == "b");
    };
    SECTION(
        "Invalid PQL query"
        "procedure a;"
        "Select a such that Calls(\"main\", a)"
    ) {
        std::vector<Token> tokens = {
            IdentityToken("procedure"), IdentityToken("a"),
            PunctuationToken(";"), IdentityToken("Select"),
            IdentityToken("a"), IdentityToken("such"),
            IdentityToken("that"), IdentityToken("Calls"),
            PunctuationToken("("), PunctuationToken("\""),
            IdentityToken("main"), PunctuationToken("\""),
            PunctuationToken(","), IdentityToken("a"),
            PunctuationToken(")")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::OK);
        REQUIRE(aq.getSelectionList().size() == 1);
        REQUIRE(aq.getSelectionList()[0]->getValue() == "a");
        REQUIRE(aq.getClauseList().size() == 1);
        std::string test = aq.getClauseList()[0].get()->getArgumentList()[0]->getValue();
        std::string test2 = aq.getClauseList()[0].get()->getArgumentList()[1]->getValue();
        REQUIRE(test == "main");
        REQUIRE(test2 == "a");
    };

    SECTION(
        "Invalid PQL query"
        "procedure a;"
        "Select a such that Calls*(a, \"main\")"
    ) {
        std::vector<Token> tokens = {
            IdentityToken("procedure"), IdentityToken("a"),
            PunctuationToken(";"), IdentityToken("Select"),
            IdentityToken("a"), IdentityToken("such"),
            IdentityToken("that"), IdentityToken("Calls"), PunctuationToken("*"),
            PunctuationToken("("), IdentityToken("a"),
            PunctuationToken(","), PunctuationToken("\""),
            IdentityToken("main"), PunctuationToken("\""),
            PunctuationToken(")")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::OK);
        REQUIRE(aq.getSelectionList().size() == 1);
        REQUIRE(aq.getSelectionList()[0]->getValue() == "a");
        REQUIRE(aq.getClauseList().size() == 1);
        std::string test = aq.getClauseList()[0].get()->getArgumentList()[0]->getValue();
        std::string test2 = aq.getClauseList()[0].get()->getArgumentList()[1]->getValue();
        REQUIRE(test == "a");
        REQUIRE(test2 == "main");
    };

    SECTION(
        "Invalid PQL query"
        "procedure a;"
        "Select a such that Calls(_, \"main\")"
    ) {
        std::vector<Token> tokens = {
            IdentityToken("procedure"), IdentityToken("a"),
            PunctuationToken(";"), IdentityToken("Select"),
            IdentityToken("a"), IdentityToken("such"),
            IdentityToken("that"), IdentityToken("Calls"),
            PunctuationToken("("), PunctuationToken("_"),
            PunctuationToken(","), PunctuationToken("\""),
            IdentityToken("main"), PunctuationToken("\""),
            PunctuationToken(")")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::OK);
        REQUIRE(aq.getSelectionList().size() == 1);
        REQUIRE(aq.getSelectionList()[0]->getValue() == "a");
        REQUIRE(aq.getClauseList().size() == 1);
        std::shared_ptr<Argument> test = aq.getClauseList()[0].get()->getArgumentList()[0];
        std::string test2 = aq.getClauseList()[0].get()->getArgumentList()[1]->getValue();
        REQUIRE(WildcardEntity::checkInstance(test.get()));
        REQUIRE(test2 == "main");
    };

    SECTION(
        "Invalid PQL query"
        "stmt a;"
        "Select a such that Calls*(\"x\", a)"
    ) {
        std::vector<Token> tokens = {
            IdentityToken("stmt"), IdentityToken("a"),
            PunctuationToken(";"), IdentityToken("Select"),
            IdentityToken("a"), IdentityToken("such"),
            IdentityToken("that"), IdentityToken("Calls"),
            PunctuationToken("*"), PunctuationToken("("),
            PunctuationToken("\""), IdentityToken("x"),
            PunctuationToken("\""), PunctuationToken(","),
            IdentityToken("a"), PunctuationToken(")")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::SEMANTIC);
    };

    SECTION(
        "Invalid PQL query"
        "stmt a;"
        "Select a such that Calls*(\"x\", 12)"
    ) {
        std::vector<Token> tokens = {
            IdentityToken("stmt"), IdentityToken("a"),
            PunctuationToken(";"), IdentityToken("Select"),
            IdentityToken("a"), IdentityToken("such"),
            IdentityToken("that"), IdentityToken("Calls"),
            PunctuationToken("*"), PunctuationToken("("),
            PunctuationToken("\""), IdentityToken("x"),
            PunctuationToken("\""), PunctuationToken(","),
            NumberToken("12"), PunctuationToken(")")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        try {
            pm.parse(tokens, aq);
            FAIL("Non-procedure passed in as argument!");
        } catch (ParserError pe) {
            REQUIRE(pe.status() == ErrorStatus::SYNTAX);
        }
    };
}
TEST_CASE("QPS attRef Parser Tests") {
    SECTION(
        "Valid PQL query, entity name is Select"
        "while a, b;"
        "Select a.stmt#"
    ) {
        std::vector<Token> tokens = {
            IdentityToken("while"), IdentityToken("a"),
            PunctuationToken(","), IdentityToken("b"),
            PunctuationToken(";"), IdentityToken("Select"),
            IdentityToken("a"), PunctuationToken("."), IdentityToken("stmt"), PunctuationToken("#")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::OK);
        REQUIRE(aq.getSelectionList().size() == 1);
        REQUIRE(aq.getSelectionList()[0]->getValue() == "a");
        REQUIRE(aq.getSelectionList()[0]->getAttrRef() == StmtEntity::TYPE_NAME + "#");
    };
    SECTION(
        "Valid PQL query, entity name is Select"
        "procedure a, b;"
        "Select a.procName"
    ) {
        std::vector<Token> tokens = {
            IdentityToken("procedure"), IdentityToken("a"),
            PunctuationToken(","), IdentityToken("b"),
            PunctuationToken(";"), IdentityToken("Select"),
            IdentityToken("a"), PunctuationToken("."), IdentityToken("procName")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::OK);
        REQUIRE(aq.getSelectionList().size() == 1);
        REQUIRE(aq.getSelectionList()[0]->getValue() == "a");
        REQUIRE(aq.getSelectionList()[0]->getAttrRef() == "procName");
    };
    SECTION(
        "procedure a, b;"
        "Select a.varName"
    ) {
        std::vector<Token> tokens = {
            IdentityToken("procedure"), IdentityToken("a"),
            PunctuationToken(","), IdentityToken("b"),
            PunctuationToken(";"), IdentityToken("Select"),
            IdentityToken("a"), PunctuationToken("."), IdentityToken("varName")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::SEMANTIC);
    };

    SECTION(
        "constant a, b;"
        "Select a.stmt#"
    ) {
        std::vector<Token> tokens = {
            IdentityToken("constant"), IdentityToken("a"),
            PunctuationToken(","), IdentityToken("b"),
            PunctuationToken(";"), IdentityToken("Select"),
            IdentityToken("a"), PunctuationToken("."),
            IdentityToken("stmt"), PunctuationToken("#")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::SEMANTIC);
    };

    SECTION(
        "call a;"
        "Select a.procName"
    ) {
        std::vector<Token> tokens = {
            IdentityToken("call"), IdentityToken("a"),
            PunctuationToken(";"), IdentityToken("Select"),
            IdentityToken("a"), PunctuationToken("."), IdentityToken("procName")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::OK);
        REQUIRE(aq.getSelectionList().size() == 1);
        REQUIRE(aq.getSelectionList()[0]->getValue() == "a");
        REQUIRE(aq.getSelectionList()[0]->getAttrRef() == "procName");
    };

    SECTION(
        "call a; stmt p;"
        "Select <a.procName, p.stmt#>"
    ) {
        std::vector<Token> tokens = {
            IdentityToken("call"), IdentityToken("a"),
            PunctuationToken(";"), IdentityToken("stmt"), IdentityToken("p"),
            PunctuationToken(";"), IdentityToken("Select"),
            PunctuationToken("<"), IdentityToken("a"), PunctuationToken("."),
            IdentityToken("procName"), PunctuationToken(","),
            IdentityToken("p"), PunctuationToken("."), IdentityToken("stmt"),
            PunctuationToken("#"), PunctuationToken(">")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::OK);
        REQUIRE(aq.getSelectionList().size() == 2);
        REQUIRE(aq.getSelectionList()[0]->getValue() == "a");
        REQUIRE(aq.getSelectionList()[0]->getAttrRef() == "procName");
        REQUIRE(aq.getSelectionList()[1]->getValue() == "p");
        REQUIRE(aq.getSelectionList()[1]->getAttrRef() == "stmt#");
    };

    SECTION(
        "call a; procedure p;"
        "Select <a.procName>"
    ) {
        std::vector<Token> tokens = {
            IdentityToken("call"), IdentityToken("a"),
            PunctuationToken(";"), IdentityToken("procedure"), IdentityToken("p"),
            PunctuationToken(";"), IdentityToken("Select"),
            PunctuationToken("<"), IdentityToken("a"), PunctuationToken("."),
            IdentityToken("procName"), PunctuationToken(">")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::OK);
        REQUIRE(aq.getSelectionList().size() == 1);
        REQUIRE(aq.getSelectionList()[0]->getValue() == "a");
        REQUIRE(aq.getSelectionList()[0]->getAttrRef() == "procName");
    };

    SECTION(
        "variable v; read r; print p; constant c;"
        "Select <v.varName, r.varName, p.varName, c.value>"
    ) {
        std::vector<Token> tokens = {
            IdentityToken("variable"), IdentityToken("v"),
            PunctuationToken(";"), IdentityToken("read"), IdentityToken("r"),
            PunctuationToken(";"), IdentityToken("print"), IdentityToken("p"),
            PunctuationToken(";"), IdentityToken("constant"), IdentityToken("c"),
            PunctuationToken(";"), IdentityToken("Select"),
            PunctuationToken("<"), IdentityToken("v"), PunctuationToken("."),
            IdentityToken("varName"), PunctuationToken(","), IdentityToken("r"), PunctuationToken("."),
            IdentityToken("varName"), PunctuationToken(","), IdentityToken("p"), PunctuationToken("."),
            IdentityToken("varName"), PunctuationToken(","), IdentityToken("c"), PunctuationToken("."),
            IdentityToken("value"), PunctuationToken(">")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::OK);
        REQUIRE(aq.getSelectionList().size() == 4);
        REQUIRE(aq.getSelectionList()[0]->getValue() == "v");
        REQUIRE(aq.getSelectionList()[0]->getAttrRef() == "varName");
        REQUIRE(aq.getSelectionList()[1]->getValue() == "r");
        REQUIRE(aq.getSelectionList()[1]->getAttrRef() == "varName");
        REQUIRE(aq.getSelectionList()[2]->getValue() == "p");
        REQUIRE(aq.getSelectionList()[2]->getAttrRef() == "varName");
        REQUIRE(aq.getSelectionList()[3]->getValue() == "c");
        REQUIRE(aq.getSelectionList()[3]->getAttrRef() == "value");
    };
}

TEST_CASE("QPS while pattern parser") {
    SECTION(
        "Valid PQL query, ideal query"
        "while a;"
        "Select a pattern a(\"x\",_)"
    ) {
        std::vector<Token> tokens = {
            IdentityToken("while"), IdentityToken("a"),
            PunctuationToken(";"), IdentityToken("Select"),
            IdentityToken("a"), IdentityToken("pattern"),
            IdentityToken("a"), PunctuationToken("("),
            PunctuationToken("\""), IdentityToken("x"),
            PunctuationToken("\""), PunctuationToken(","),
            PunctuationToken("_"), PunctuationToken(")")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::OK);
        REQUIRE(aq.getSelectionList().size() == 1);
        REQUIRE(aq.getSelectionList()[0]->getValue() == "a");
        REQUIRE(aq.getClauseList().size() == 1);
        std::string test = aq.getClauseList()[0].get()->getArgumentList()[0]->getValue();
        std::string test2 = aq.getClauseList()[0].get()->getArgumentList()[1]->getValue();
        REQUIRE(test == "a");
        REQUIRE(test2 == "x");
    };

    SECTION(
        "Valid PQL query, ideal query"
        "while a; variable v;"
        "Select a pattern a(v, _)"
    ) {
        std::vector<Token> tokens = {
            IdentityToken("while"), IdentityToken("a"),
            PunctuationToken(";"), IdentityToken("variable"),
            IdentityToken("v"), PunctuationToken(";"), IdentityToken("Select"),
            IdentityToken("a"), IdentityToken("pattern"),
            IdentityToken("a"), PunctuationToken("("),
            IdentityToken("v"), PunctuationToken(","),
            PunctuationToken("_"), PunctuationToken(")")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::OK);
        REQUIRE(aq.getSelectionList().size() == 1);
        REQUIRE(aq.getSelectionList()[0]->getValue() == "a");
        REQUIRE(aq.getClauseList().size() == 1);
        std::string test = aq.getClauseList()[0].get()->getArgumentList()[0]->getValue();
        std::string test2 = aq.getClauseList()[0].get()->getArgumentList()[1]->getValue();
        REQUIRE(test == "a");
        REQUIRE(test2 == "v");
    };

    SECTION(
        "Valid PQL query, ideal query"
        "while a; variable v;"
        "Select a pattern a(_, _)"
    ) {
        std::vector<Token> tokens = {
            IdentityToken("while"), IdentityToken("a"),
            PunctuationToken(";"), IdentityToken("variable"),
            IdentityToken("v"), PunctuationToken(";"), IdentityToken("Select"),
            IdentityToken("a"), IdentityToken("pattern"),
            IdentityToken("a"), PunctuationToken("("),
            PunctuationToken("_"), PunctuationToken(","),
            PunctuationToken("_"), PunctuationToken(")")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::OK);
        REQUIRE(aq.getSelectionList().size() == 1);
        REQUIRE(aq.getSelectionList()[0]->getValue() == "a");
        REQUIRE(aq.getClauseList().size() == 1);
        std::string test = aq.getClauseList()[0].get()->getArgumentList()[0]->getValue();
        std::string test2 = aq.getClauseList()[0].get()->getArgumentList()[1]->getValue();
        REQUIRE(test == "a");
        REQUIRE(test2 == "");
    };

    SECTION(
        "Invalid PQL query, space between numbers"
        "while a; variable v;"
        "Select v pattern a(v,_,_)"
    ) {
        std::vector<Token> tokens = {
            IdentityToken("while"), IdentityToken("a"),
            PunctuationToken(";"), IdentityToken("variable"),
            IdentityToken("v"), PunctuationToken(";"), IdentityToken("Select"),
            IdentityToken("a"), IdentityToken("pattern"),
            IdentityToken("a"), PunctuationToken("("),
            IdentityToken("v"), PunctuationToken(","),
            PunctuationToken("_"), PunctuationToken(","), PunctuationToken("_"), PunctuationToken(")")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::SEMANTIC);
    };

    SECTION(
        "Invalid PQL query, space between numbers"
        "while a; variable v;"
        "Select v pattern a(v, 2)"
    ) {
        std::vector<Token> tokens = {
            IdentityToken("while"), IdentityToken("a"),
            PunctuationToken(";"), IdentityToken("variable"),
            IdentityToken("v"), PunctuationToken(";"), IdentityToken("Select"),
            IdentityToken("a"), IdentityToken("pattern"),
            IdentityToken("a"), PunctuationToken("("),
            IdentityToken("v"), PunctuationToken(","),
            NumberToken("2"), PunctuationToken(")")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        try {
            pm.parse(tokens, aq);
            FAIL("Second argument can only be wildcard!");
        } catch (ParserError pe) {
            REQUIRE(pe.status() == ErrorStatus::SYNTAX);
        }
    };
}

TEST_CASE("QPS if pattern parser") {
    SECTION(
        "if a;"
        "Select a pattern a(\"x\",_ ,_)"
    ) {
        std::vector<Token> tokens = {
            IdentityToken("if"), IdentityToken("a"),
            PunctuationToken(";"), IdentityToken("Select"),
            IdentityToken("a"), IdentityToken("pattern"),
            IdentityToken("a"), PunctuationToken("("),
            PunctuationToken("\""), IdentityToken("x"),
            PunctuationToken("\""), PunctuationToken(","),
            PunctuationToken("_"), PunctuationToken(","),
            PunctuationToken("_"), PunctuationToken(")")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::OK);
        REQUIRE(aq.getSelectionList().size() == 1);
        REQUIRE(aq.getSelectionList()[0]->getValue() == "a");
        REQUIRE(aq.getClauseList().size() == 1);
        std::string test = aq.getClauseList()[0].get()->getArgumentList()[0]->getValue();
        std::string test2 = aq.getClauseList()[0].get()->getArgumentList()[1]->getValue();
        REQUIRE(test == "a");
        REQUIRE(test2 == "x");
    };

    SECTION(
        "Valid PQL query, ideal query"
        "if a; variable v;"
        "Select a pattern a(_, _, _)"
    ) {
        std::vector<Token> tokens = {
            IdentityToken("if"), IdentityToken("a"),
            PunctuationToken(";"), IdentityToken("variable"),
            IdentityToken("v"), PunctuationToken(";"), IdentityToken("Select"),
            IdentityToken("a"), IdentityToken("pattern"),
            IdentityToken("a"), PunctuationToken("("),
            PunctuationToken("_"), PunctuationToken(","),
            PunctuationToken("_"), PunctuationToken(","),
            PunctuationToken("_"), PunctuationToken(")")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::OK);
        REQUIRE(aq.getSelectionList().size() == 1);
        REQUIRE(aq.getSelectionList()[0]->getValue() == "a");
        REQUIRE(aq.getClauseList().size() == 1);
        std::string test = aq.getClauseList()[0].get()->getArgumentList()[0]->getValue();
        std::string test2 = aq.getClauseList()[0].get()->getArgumentList()[1]->getValue();
        REQUIRE(test == "a");
        REQUIRE(test2 == "");
    };

    SECTION(
        "if a; variable v;"
        "Select v pattern a(v,_)"
    ) {
        std::vector<Token> tokens = {
            IdentityToken("if"), IdentityToken("a"),
            PunctuationToken(";"), IdentityToken("variable"),
            IdentityToken("v"), PunctuationToken(";"), IdentityToken("Select"),
            IdentityToken("a"), IdentityToken("pattern"),
            IdentityToken("a"), PunctuationToken("("),
            IdentityToken("v"), PunctuationToken(","),
            PunctuationToken("_"), PunctuationToken(")")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::SEMANTIC);
        };

}

TEST_CASE("QPS With Parser Tests") {
    SECTION(
        "Valid PQL query, ideal query"
        "assign a;"
        "Select a with a.stmt# = 2"
    ) {
        std::vector<Token> tokens = {
            IdentityToken("assign"), IdentityToken("a"),
            PunctuationToken(";"), IdentityToken("Select"),
            IdentityToken("a"), IdentityToken("with"),
            IdentityToken("a"), PunctuationToken("."),
            IdentityToken("stmt"), PunctuationToken("#"),
            PunctuationToken("="), NumberToken("2")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::OK);
        REQUIRE(aq.getSelectionList().size() == 1);
        REQUIRE(aq.getSelectionList()[0]->getValue() == "a");
        REQUIRE(aq.getClauseList().size() == 1);
        std::string test = aq.getClauseList()[0].get()->getArgumentList()[0]->getValue();
        std::string test2 = aq.getClauseList()[0].get()->getArgumentList()[1]->getValue();
        REQUIRE(test == "a");
        REQUIRE(test2 == "2");
    };

    SECTION(
        "Valid PQL query, ideal query"
        "assign a;"
        "Select a with a = 2"
    ) {
        std::vector<Token> tokens = {
            IdentityToken("assign"), IdentityToken("a"),
            PunctuationToken(";"), IdentityToken("Select"),
            IdentityToken("a"), IdentityToken("with"),
            IdentityToken("a"),
            PunctuationToken("="), NumberToken("2")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        try {
            pm.parse(tokens, aq);
            FAIL("With clause cannot take in synonyms!");
        } catch (ParserError pe) {
            REQUIRE(pe.status() == ErrorStatus::SYNTAX);
        }
    };

    SECTION(
        "Valid PQL query, ideal query"
        "procedure a;"
        "Select a with a.procName = \"x\""
    ) {
        std::vector<Token> tokens = {
            IdentityToken("procedure"), IdentityToken("a"),
            PunctuationToken(";"), IdentityToken("Select"),
            IdentityToken("a"), IdentityToken("with"),
            IdentityToken("a"), PunctuationToken("."),
            IdentityToken("procName"),
            PunctuationToken("="), PunctuationToken("\""),
            IdentityToken("x"), PunctuationToken("\"")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::OK);
        REQUIRE(aq.getSelectionList().size() == 1);
        REQUIRE(aq.getSelectionList()[0]->getValue() == "a");
        REQUIRE(aq.getClauseList().size() == 1);
        std::string test = aq.getClauseList()[0].get()->getArgumentList()[0]->getValue();
        std::string test2 = aq.getClauseList()[0].get()->getArgumentList()[1]->getValue();
        REQUIRE(test == "a");
        REQUIRE(test2 == "x");
    };

    SECTION(
        "procedure a"
        "Select a with a.procName = \"x\""
    ) {
        std::vector<Token> tokens = {
            IdentityToken("procedure"), IdentityToken("a"),
            PunctuationToken(";"), IdentityToken("Select"),
            IdentityToken("a"), IdentityToken("with"),
            IdentityToken("a"), PunctuationToken("."),
            IdentityToken("procName"),
            PunctuationToken("="), NumberToken("2")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::SEMANTIC);
    };

    SECTION(
        "Valid PQL query, ideal query"
        "procedure a, b;"
        "Select a with a.procName = b.procName"
    ) {
        std::vector<Token> tokens = {
            IdentityToken("procedure"), IdentityToken("a"),
            PunctuationToken(","), IdentityToken("b"),
            PunctuationToken(";"), IdentityToken("Select"),
            IdentityToken("a"), IdentityToken("with"),
            IdentityToken("a"), PunctuationToken("."),
            IdentityToken("procName"),
            PunctuationToken("="), IdentityToken("b"),
            PunctuationToken("."), IdentityToken("procName")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::OK);
        REQUIRE(aq.getSelectionList().size() == 1);
        REQUIRE(aq.getSelectionList()[0]->getValue() == "a");
        REQUIRE(aq.getClauseList().size() == 1);
        std::string test = aq.getClauseList()[0].get()->getArgumentList()[0]->getValue();
        std::string test2 = aq.getClauseList()[0].get()->getArgumentList()[1]->getValue();
        REQUIRE(test == "a");
        REQUIRE(test2 == "b");
    };

    SECTION(
        "Valid PQL query, ideal query"
        "procedure a, b;"
        "Select a with 2 = b.procName"
    ) {
        std::vector<Token> tokens = {
            IdentityToken("procedure"), IdentityToken("a"),
            PunctuationToken(","), IdentityToken("b"),
            PunctuationToken(";"), IdentityToken("Select"),
            IdentityToken("a"), IdentityToken("with"),
            NumberToken("2"),
            PunctuationToken("="), IdentityToken("b"),
            PunctuationToken("."), IdentityToken("procName")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::SEMANTIC);
    };

    SECTION(
        "Valid PQL query, ideal query"
        "constant a, b;"
        "Select a with a.value = 2"
    ) {
        std::vector<Token> tokens = {
            IdentityToken("constant"), IdentityToken("a"),
            PunctuationToken(","), IdentityToken("b"),
            PunctuationToken(";"), IdentityToken("Select"),
            IdentityToken("a"), IdentityToken("with"),
            IdentityToken("a"), PunctuationToken("."),
            IdentityToken("value"),
            PunctuationToken("="), NumberToken("2")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::OK);
        REQUIRE(aq.getSelectionList().size() == 1);
        REQUIRE(aq.getSelectionList()[0]->getValue() == "a");
        REQUIRE(aq.getClauseList().size() == 1);
        std::string test = aq.getClauseList()[0].get()->getArgumentList()[0]->getValue();
        std::string test2 = aq.getClauseList()[0].get()->getArgumentList()[1]->getValue();
        REQUIRE(test == "a");
        REQUIRE(test2 == "2");
    };

    SECTION(
        "procedure a, b;"
        "Select a with and"
    ) {
        std::vector<Token> tokens = {
            IdentityToken("procedure"), IdentityToken("a"),
            PunctuationToken(","), IdentityToken("b"),
            PunctuationToken(";"), IdentityToken("Select"),
            IdentityToken("a"), IdentityToken("with"),
            IdentityToken("and"),
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        try {
            pm.parse(tokens, aq);
        } catch (ParserError pe) {
            REQUIRE(pe.status() == ErrorStatus::SYNTAX);
        }
    };

    SECTION(
        "Valid PQL query, ideal query"
        "constant a; print b; stmt c; call d;"
        "Select <a, d.stmt#> with a.value = 2 and \"heehee\" = b.varName and 3 = c.stmt# and d.procName = \"hoho\""
    ) {
        std::vector<Token> tokens = {
            IdentityToken("constant"), IdentityToken("a"),
            PunctuationToken(";"), IdentityToken("print"), IdentityToken("b"),
            PunctuationToken(";"), IdentityToken("stmt"), IdentityToken("c"),
            PunctuationToken(";"), IdentityToken("call"), IdentityToken("d"),
            PunctuationToken(";"), IdentityToken("Select"), PunctuationToken("<"),
            IdentityToken("a"), PunctuationToken(","), IdentityToken("d"),
            PunctuationToken("."), IdentityToken("stmt"), PunctuationToken("#"),
            PunctuationToken(">"), IdentityToken("with"), IdentityToken("a"),
            PunctuationToken("."), IdentityToken("value"), PunctuationToken("="),
            NumberToken("2"), IdentityToken("and"), PunctuationToken("\""),
            IdentityToken("heehee"), PunctuationToken("\""), PunctuationToken("="),
            IdentityToken("b"), PunctuationToken("."), IdentityToken("varName"),
            IdentityToken("and"), NumberToken("3"), PunctuationToken("="),
            IdentityToken("c"), PunctuationToken("."), IdentityToken("stmt"),
            PunctuationToken("#"), IdentityToken("and"), IdentityToken("d"),
            PunctuationToken("."), IdentityToken("procName"), PunctuationToken("="),
            PunctuationToken("\""),
            IdentityToken("hoho"), PunctuationToken("\"")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::OK);
        REQUIRE(aq.getSelectionList().size() == 2);
        REQUIRE(aq.getSelectionList()[0]->getValue() == "a");
        REQUIRE(aq.getSelectionList()[1]->getValue() == "d");
        REQUIRE(aq.getClauseList().size() == 4);
        REQUIRE(aq.getClauseList()[0].get()->getArgumentList()[0]->getValue() == "a");
        REQUIRE(aq.getClauseList()[0].get()->getArgumentList()[1]->getValue() == "2");
        REQUIRE(aq.getClauseList()[1].get()->getArgumentList()[0]->getValue() == "heehee");
        REQUIRE(aq.getClauseList()[1].get()->getArgumentList()[1]->getValue() == "b");
        REQUIRE(aq.getClauseList()[2].get()->getArgumentList()[0]->getValue() == "3");
        REQUIRE(aq.getClauseList()[2].get()->getArgumentList()[1]->getValue() == "c");
        REQUIRE(aq.getClauseList()[3].get()->getArgumentList()[0]->getValue() == "d");
        REQUIRE(aq.getClauseList()[3].get()->getArgumentList()[1]->getValue() == "hoho");
    };
}

TEST_CASE("QPS such that \"and\" Parser Tests") {
    SECTION(
        "Valid PQL query, ideal query"
        "assign a; variable v;"
        "Select a such that Parent(1, 2) and Uses(a,v)"
    ) {
        std::vector<Token> tokens = {
            IdentityToken("assign"), IdentityToken("a"),
            PunctuationToken(";"), IdentityToken("variable"), IdentityToken("v"),
            PunctuationToken(";"), IdentityToken("Select"),
            IdentityToken("a"), IdentityToken("such"),
            IdentityToken("that"), IdentityToken("Parent"),
            PunctuationToken("("), NumberToken("1"),
            PunctuationToken(","), NumberToken("2"),
            PunctuationToken(")"), IdentityToken("and"),
            IdentityToken("Uses"),
            PunctuationToken("("), IdentityToken("a"),
            PunctuationToken(","), IdentityToken("v"),
            PunctuationToken(")")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::OK);
        REQUIRE(aq.getSelectionList().size() == 1);
        REQUIRE(aq.getSelectionList()[0]->getValue() == "a");
        REQUIRE(aq.getClauseList().size() == 2);
        REQUIRE(aq.getClauseList()[0].get()->getArgumentList()[0]->getValue() == "1");
        REQUIRE(aq.getClauseList()[0].get()->getArgumentList()[1]->getValue() == "2");
        REQUIRE(aq.getClauseList()[1].get()->getArgumentList()[0]->getValue() == "a");
        REQUIRE(aq.getClauseList()[1].get()->getArgumentList()[1]->getValue() == "v");
    };
    SECTION(
        "Valid PQL query, ideal query"
        "assign a; variable v;"
        "Select a such that Parent(1, 2) and Uses(a,v) pattern a(v, _\"ryan\"_)"
    ) {
        std::vector<Token> tokens = {
            IdentityToken("assign"), IdentityToken("a"),
            PunctuationToken(";"), IdentityToken("variable"), IdentityToken("v"),
            PunctuationToken(";"), IdentityToken("Select"),
            IdentityToken("a"), IdentityToken("such"),
            IdentityToken("that"), IdentityToken("Parent"),
            PunctuationToken("("), NumberToken("1"),
            PunctuationToken(","), NumberToken("2"),
            PunctuationToken(")"), IdentityToken("and"),
            IdentityToken("Uses"),
            PunctuationToken("("), IdentityToken("a"),
            PunctuationToken(","), IdentityToken("v"),
            PunctuationToken(")"), IdentityToken("pattern"),
            IdentityToken("a"), PunctuationToken("("),
            IdentityToken("v"), PunctuationToken(","),
            PunctuationToken("_"), PunctuationToken("\""), IdentityToken("ryan"),
            PunctuationToken("\""), PunctuationToken("_"), PunctuationToken(")")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::OK);
        REQUIRE(aq.getSelectionList().size() == 1);
        REQUIRE(aq.getSelectionList()[0]->getValue() == "a");
        REQUIRE(aq.getClauseList().size() == 3);
        REQUIRE(aq.getClauseList()[0].get()->getArgumentList()[0]->getValue() == "1");
        REQUIRE(aq.getClauseList()[0].get()->getArgumentList()[1]->getValue() == "2");
        REQUIRE(aq.getClauseList()[1].get()->getArgumentList()[0]->getValue() == "a");
        REQUIRE(aq.getClauseList()[1].get()->getArgumentList()[1]->getValue() == "v");
        REQUIRE(aq.getClauseList()[2].get()->getArgumentList()[0]->getValue() == "a");
        REQUIRE(aq.getClauseList()[2].get()->getArgumentList()[1]->getValue() == "v");
        REQUIRE(aq.getClauseList()[2].get()->getArgumentList()[2]->getValue() == "ryan");
    };
    SECTION(
        "Valid PQL query, ideal query"
        "assign a; variable v;"
        "Select a such that Parent(1, 2) and Uses(a,v) such that Parent(2, 3)"
    ) {
        std::vector<Token> tokens = {
            IdentityToken("assign"), IdentityToken("a"),
            PunctuationToken(";"), IdentityToken("variable"), IdentityToken("v"),
            PunctuationToken(";"), IdentityToken("Select"),
            IdentityToken("a"), IdentityToken("such"),
            IdentityToken("that"), IdentityToken("Parent"),
            PunctuationToken("("), NumberToken("1"),
            PunctuationToken(","), NumberToken("2"),
            PunctuationToken(")"), IdentityToken("and"),
            IdentityToken("Uses"),
            PunctuationToken("("), IdentityToken("a"),
            PunctuationToken(","), IdentityToken("v"),
            PunctuationToken(")"), IdentityToken("such"),
            IdentityToken("that"), IdentityToken("Parent"),
            PunctuationToken("("), NumberToken("2"),
            PunctuationToken(","), NumberToken("3"),
            PunctuationToken(")")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::OK);
        REQUIRE(aq.getSelectionList().size() == 1);
        REQUIRE(aq.getSelectionList()[0]->getValue() == "a");
        REQUIRE(aq.getClauseList().size() == 3);
        REQUIRE(aq.getClauseList()[0].get()->getArgumentList()[0]->getValue() == "1");
        REQUIRE(aq.getClauseList()[0].get()->getArgumentList()[1]->getValue() == "2");
        REQUIRE(aq.getClauseList()[1].get()->getArgumentList()[0]->getValue() == "a");
        REQUIRE(aq.getClauseList()[1].get()->getArgumentList()[1]->getValue() == "v");
        REQUIRE(aq.getClauseList()[2].get()->getArgumentList()[0]->getValue() == "2");
        REQUIRE(aq.getClauseList()[2].get()->getArgumentList()[1]->getValue() == "3");
    };

    SECTION(
        "Valid PQL query, ideal query"
        "assign a; variable v;"
        "Select a such that Parent(1, 2) and Uses(a,v) such that Parent(2, 3) and Uses(a,v)"
    ) {
        std::vector<Token> tokens = {
            IdentityToken("assign"), IdentityToken("a"),
            PunctuationToken(";"), IdentityToken("variable"), IdentityToken("v"),
            PunctuationToken(";"), IdentityToken("Select"),
            IdentityToken("a"), IdentityToken("such"),
            IdentityToken("that"), IdentityToken("Parent"),
            PunctuationToken("("), NumberToken("1"),
            PunctuationToken(","), NumberToken("2"),
            PunctuationToken(")"), IdentityToken("and"),
            IdentityToken("Uses"),
            PunctuationToken("("), IdentityToken("a"),
            PunctuationToken(","), IdentityToken("v"),
            PunctuationToken(")"), IdentityToken("such"),
            IdentityToken("that"), IdentityToken("Parent"),
            PunctuationToken("("), NumberToken("2"),
            PunctuationToken(","), NumberToken("3"),
            PunctuationToken(")"), IdentityToken("and"),
            IdentityToken("Uses"),
            PunctuationToken("("), IdentityToken("a"),
            PunctuationToken(","), IdentityToken("v"),
            PunctuationToken(")")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::OK);
        REQUIRE(aq.getSelectionList().size() == 1);
        REQUIRE(aq.getSelectionList()[0]->getValue() == "a");
        REQUIRE(aq.getClauseList().size() == 4);
        REQUIRE(aq.getClauseList()[0].get()->getArgumentList()[0]->getValue() == "1");
        REQUIRE(aq.getClauseList()[0].get()->getArgumentList()[1]->getValue() == "2");
        REQUIRE(aq.getClauseList()[1].get()->getArgumentList()[0]->getValue() == "a");
        REQUIRE(aq.getClauseList()[1].get()->getArgumentList()[1]->getValue() == "v");
        REQUIRE(aq.getClauseList()[2].get()->getArgumentList()[0]->getValue() == "2");
        REQUIRE(aq.getClauseList()[2].get()->getArgumentList()[1]->getValue() == "3");
        REQUIRE(aq.getClauseList()[3].get()->getArgumentList()[0]->getValue() == "a");
        REQUIRE(aq.getClauseList()[3].get()->getArgumentList()[1]->getValue() == "v");
    };

    SECTION(
        "assign a; variable v;"
        "Select a such that Parent(1, 2) and pattern(v, _\"ryan\"_)"
    ) {
        std::vector<Token> tokens = {
            IdentityToken("assign"), IdentityToken("a"),
            PunctuationToken(";"), IdentityToken("variable"), IdentityToken("v"),
            PunctuationToken(";"), IdentityToken("Select"),
            IdentityToken("a"), IdentityToken("such"),
            IdentityToken("that"), IdentityToken("Parent"),
            PunctuationToken("("), NumberToken("1"),
            PunctuationToken(","), NumberToken("2"),
            PunctuationToken(")"), IdentityToken("and"), IdentityToken("pattern"),
            IdentityToken("a"), PunctuationToken("("),
            IdentityToken("v"), PunctuationToken(","),
            PunctuationToken("_"), PunctuationToken("\""), IdentityToken("ryan"),
            PunctuationToken("\""), PunctuationToken("_"), PunctuationToken(")")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        try {
            pm.parse(tokens, aq);
            FAIL("Ended such that with a pattern!");
        } catch (ParserError pe) {
            REQUIRE(pe.status() == ErrorStatus::SYNTAX);
        }
    };
    SECTION(
        "assign a; variable v;"
        "Select a such that Parent(1, 2) and "
    ) {
        std::vector<Token> tokens = {
            IdentityToken("assign"), IdentityToken("a"),
            PunctuationToken(";"), IdentityToken("variable"), IdentityToken("v"),
            PunctuationToken(";"), IdentityToken("Select"),
            IdentityToken("a"), IdentityToken("such"),
            IdentityToken("that"), IdentityToken("Parent"),
            PunctuationToken("("), NumberToken("1"),
            PunctuationToken(","), NumberToken("2"),
            PunctuationToken(")"), IdentityToken("and")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        try {
            pm.parse(tokens, aq);
            FAIL("Ended such that with a \"and\"!");
        } catch (ParserError pe) {
            REQUIRE(pe.status() == ErrorStatus::SYNTAX);
        }
    };

    SECTION(
        "assign a; variable v;"
        "Select a and Parent(1, 2)"
    ) {
        std::vector<Token> tokens = {
            IdentityToken("assign"), IdentityToken("a"),
            PunctuationToken(";"), IdentityToken("variable"), IdentityToken("v"),
            PunctuationToken(";"), IdentityToken("Select"),
            IdentityToken("a"), IdentityToken("and"), IdentityToken("Parent"),
            PunctuationToken("("), NumberToken("1"),
            PunctuationToken(","), NumberToken("2"),
            PunctuationToken(")")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        try {
            pm.parse(tokens, aq);
            FAIL("Started with an \"and\"!");
        } catch (ParserError pe) {
            REQUIRE(pe.status() == ErrorStatus::SYNTAX);
        }
    };
}
TEST_CASE("QPS pattern \"and\" Parser Tests") {
    SECTION(
        "Valid PQL query, ideal query"
        "assign a, a1; variable v, v1;"
        "Select a pattern a(v, _\"ryan\"_) and a1(v1, _\"ryan\"_)"
    ) {
        std::vector<Token> tokens = {
            IdentityToken("assign"), IdentityToken("a"),
            PunctuationToken(","), IdentityToken("a1"),
            PunctuationToken(";"), IdentityToken("variable"), IdentityToken("v"),
            PunctuationToken(","), IdentityToken("v1"),
            PunctuationToken(";"), IdentityToken("Select"),
            IdentityToken("a"), IdentityToken("pattern"),
            IdentityToken("a"), PunctuationToken("("),
            IdentityToken("v"), PunctuationToken(","),
            PunctuationToken("_"), PunctuationToken("\""), IdentityToken("ryan"),
            PunctuationToken("\""), PunctuationToken("_"), PunctuationToken(")"),
            IdentityToken("and"), IdentityToken("a1"), PunctuationToken("("),
            IdentityToken("v1"), PunctuationToken(","),
            PunctuationToken("_"), PunctuationToken("\""), IdentityToken("ryan"),
            PunctuationToken("\""), PunctuationToken("_"), PunctuationToken(")")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::OK);
        REQUIRE(aq.getSelectionList().size() == 1);
        REQUIRE(aq.getSelectionList()[0]->getValue() == "a");
        REQUIRE(aq.getClauseList().size() == 2);
        REQUIRE(aq.getClauseList()[0].get()->getArgumentList()[0]->getValue() == "a");
        REQUIRE(aq.getClauseList()[0].get()->getArgumentList()[1]->getValue() == "v");
        REQUIRE(aq.getClauseList()[0].get()->getArgumentList()[2]->getValue() == "ryan");
        REQUIRE(aq.getClauseList()[1].get()->getArgumentList()[0]->getValue() == "a1");
        REQUIRE(aq.getClauseList()[1].get()->getArgumentList()[1]->getValue() == "v1");
        REQUIRE(aq.getClauseList()[1].get()->getArgumentList()[2]->getValue() == "ryan");
    };

    SECTION(
        "Valid PQL query, ideal query"
        "assign a, a1; variable v, v1;"
        "Select a pattern a(v, _\"ryan\"_) and a1(v1, _\"ryan\"_) and a(v1, _)"
    ) {
        std::vector<Token> tokens = {
            IdentityToken("assign"), IdentityToken("a"),
            PunctuationToken(","), IdentityToken("a1"),
            PunctuationToken(";"), IdentityToken("variable"), IdentityToken("v"),
            PunctuationToken(","), IdentityToken("v1"),
            PunctuationToken(";"), IdentityToken("Select"),
            IdentityToken("a"), IdentityToken("pattern"),
            IdentityToken("a"), PunctuationToken("("),
            IdentityToken("v"), PunctuationToken(","),
            PunctuationToken("_"), PunctuationToken("\""), IdentityToken("ryan"),
            PunctuationToken("\""), PunctuationToken("_"), PunctuationToken(")"),
            IdentityToken("and"), IdentityToken("a1"), PunctuationToken("("),
            IdentityToken("v1"), PunctuationToken(","),
            PunctuationToken("_"), PunctuationToken("\""), IdentityToken("ryan"),
            PunctuationToken("\""), PunctuationToken("_"), PunctuationToken(")"),
            IdentityToken("and"), IdentityToken("a"), PunctuationToken("("),
            IdentityToken("v1"), PunctuationToken(","),
            PunctuationToken("_"), PunctuationToken(")")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::OK);
        REQUIRE(aq.getSelectionList().size() == 1);
        REQUIRE(aq.getSelectionList()[0]->getValue() == "a");
        REQUIRE(aq.getClauseList().size() == 3);
        REQUIRE(aq.getClauseList()[0].get()->getArgumentList()[0]->getValue() == "a");
        REQUIRE(aq.getClauseList()[0].get()->getArgumentList()[1]->getValue() == "v");
        REQUIRE(aq.getClauseList()[0].get()->getArgumentList()[2]->getValue() == "ryan");
        REQUIRE(aq.getClauseList()[1].get()->getArgumentList()[0]->getValue() == "a1");
        REQUIRE(aq.getClauseList()[1].get()->getArgumentList()[1]->getValue() == "v1");
        REQUIRE(aq.getClauseList()[1].get()->getArgumentList()[2]->getValue() == "ryan");
        REQUIRE(aq.getClauseList()[2].get()->getArgumentList()[0]->getValue() == "a");
        REQUIRE(aq.getClauseList()[2].get()->getArgumentList()[1]->getValue() == "v1");
        REQUIRE(aq.getClauseList()[2].get()->getArgumentList()[2]->getValue() == "");
    };

    SECTION(
        "Valid PQL query, ideal query"
        "assign a, a1; variable v, v1;"
        "Select a pattern a(v, _\"ryan\"_) and a1(v1, _\"ryan\"_) such that Parent(1, 2) and Uses(a1, v)"
    ) {
        std::vector<Token> tokens = {
            IdentityToken("assign"), IdentityToken("a"),
            PunctuationToken(","), IdentityToken("a1"),
            PunctuationToken(";"), IdentityToken("variable"), IdentityToken("v"),
            PunctuationToken(","), IdentityToken("v1"),
            PunctuationToken(";"), IdentityToken("Select"),
            IdentityToken("a"), IdentityToken("pattern"),
            IdentityToken("a"), PunctuationToken("("),
            IdentityToken("v"), PunctuationToken(","),
            PunctuationToken("_"), PunctuationToken("\""), IdentityToken("ryan"),
            PunctuationToken("\""), PunctuationToken("_"), PunctuationToken(")"),
            IdentityToken("and"), IdentityToken("a1"), PunctuationToken("("),
            IdentityToken("v1"), PunctuationToken(","),
            PunctuationToken("_"), PunctuationToken("\""), IdentityToken("ryan"),
            PunctuationToken("\""), PunctuationToken("_"), PunctuationToken(")"),
            IdentityToken("such"), IdentityToken("that"), IdentityToken("Parent"),
            PunctuationToken("("), NumberToken("1"),
            PunctuationToken(","), NumberToken("2"),
            PunctuationToken(")"), IdentityToken("and"),
            IdentityToken("Uses"),
            PunctuationToken("("), IdentityToken("a1"),
            PunctuationToken(","), IdentityToken("v"),
            PunctuationToken(")")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::OK);
        REQUIRE(aq.getSelectionList().size() == 1);
        REQUIRE(aq.getSelectionList()[0]->getValue() == "a");
        REQUIRE(aq.getClauseList().size() == 4);
        REQUIRE(aq.getClauseList()[0].get()->getArgumentList()[0]->getValue() == "a");
        REQUIRE(aq.getClauseList()[0].get()->getArgumentList()[1]->getValue() == "v");
        REQUIRE(aq.getClauseList()[0].get()->getArgumentList()[2]->getValue() == "ryan");
        REQUIRE(aq.getClauseList()[1].get()->getArgumentList()[0]->getValue() == "a1");
        REQUIRE(aq.getClauseList()[1].get()->getArgumentList()[1]->getValue() == "v1");
        REQUIRE(aq.getClauseList()[1].get()->getArgumentList()[2]->getValue() == "ryan");
        REQUIRE(aq.getClauseList()[2].get()->getArgumentList()[0]->getValue() == "1");
        REQUIRE(aq.getClauseList()[2].get()->getArgumentList()[1]->getValue() == "2");
        REQUIRE(aq.getClauseList()[3].get()->getArgumentList()[0]->getValue() == "a1");
        REQUIRE(aq.getClauseList()[3].get()->getArgumentList()[1]->getValue() == "v");
    };

    SECTION(
        "Valid PQL query, ideal query"
        "assign a, a1; variable v, v1;"
        "Select a pattern a(v, _\"ryan\"_) and"
    ) {
        std::vector<Token> tokens = {
            IdentityToken("assign"), IdentityToken("a"),
            PunctuationToken(","), IdentityToken("a1"),
            PunctuationToken(";"), IdentityToken("variable"), IdentityToken("v"),
            PunctuationToken(","), IdentityToken("v1"),
            PunctuationToken(";"), IdentityToken("Select"),
            IdentityToken("a"), IdentityToken("pattern"),
            IdentityToken("a"), PunctuationToken("("),
            IdentityToken("v"), PunctuationToken(","),
            PunctuationToken("_"), PunctuationToken("\""), IdentityToken("ryan"),
            PunctuationToken("\""), PunctuationToken("_"), PunctuationToken(")"),
            IdentityToken("and")
        };
        try {
            ParserManager pm = ParserManager();
            AbstractQuery aq;
            pm.parse(tokens, aq);
            FAIL("ended with and!");
        } catch (ParserError pe) {
            REQUIRE(pe.status() == ErrorStatus::SYNTAX);
        }
    };

    SECTION(
        "assign a, a1; variable v, v1;"
        "Select a pattern a(v, _\"ryan\"_) and Parent(_, _)"
    ) {
        std::vector<Token> tokens = {
            IdentityToken("assign"), IdentityToken("a"),
            PunctuationToken(","), IdentityToken("a1"),
            PunctuationToken(";"), IdentityToken("variable"), IdentityToken("v"),
            PunctuationToken(","), IdentityToken("v1"),
            PunctuationToken(";"), IdentityToken("Select"),
            IdentityToken("a"), IdentityToken("pattern"),
            IdentityToken("a"), PunctuationToken("("),
            IdentityToken("v"), PunctuationToken(","),
            PunctuationToken("_"), PunctuationToken("\""), IdentityToken("ryan"),
            PunctuationToken("\""), PunctuationToken("_"), PunctuationToken(")"),
            IdentityToken("and"), IdentityToken("Parent"),
            PunctuationToken("("), NumberToken("_"),
            PunctuationToken(","), NumberToken("_"),
            PunctuationToken(")")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::SEMANTIC);
    };

    SECTION(
        "Valid PQL query, ideal query"
        "if a; assign b; while c; variable d;"
        "Select <a, b, c> pattern a(_, _, _) and b(d, _) and c(\"x\",_)"
    ) {
        std::vector<Token> tokens = {
            IdentityToken("if"), IdentityToken("a"),
            PunctuationToken(";"), IdentityToken("assign"), IdentityToken("b"),
            PunctuationToken(";"), IdentityToken("while"), IdentityToken("c"),
            PunctuationToken(";"), IdentityToken("variable"),
            IdentityToken("d"), PunctuationToken(";"), IdentityToken("Select"),
            PunctuationToken("<"), IdentityToken("a"), PunctuationToken(","),
            IdentityToken("b"), PunctuationToken(","), IdentityToken("c"),
            PunctuationToken(">"), IdentityToken("pattern"),
            IdentityToken("a"), PunctuationToken("("),
            PunctuationToken("_"), PunctuationToken(","),
            PunctuationToken("_"), PunctuationToken(","),
            PunctuationToken("_"), PunctuationToken(")"),
            IdentityToken("and"), IdentityToken("b"), PunctuationToken("("),
            IdentityToken("d"), PunctuationToken(","),
            PunctuationToken("_"), PunctuationToken(")"),
            IdentityToken("and"), IdentityToken("c"), PunctuationToken("("),
            PunctuationToken("\""), IdentityToken("x"), PunctuationToken("\""),
            PunctuationToken(","), PunctuationToken("_"), PunctuationToken(")"),
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::OK);
        REQUIRE(aq.getSelectionList().size() == 3);
        REQUIRE(aq.getSelectionList()[0]->getValue() == "a");
        REQUIRE(aq.getSelectionList()[1]->getValue() == "b");
        REQUIRE(aq.getSelectionList()[2]->getValue() == "c");
        REQUIRE(aq.getClauseList().size() == 3);
        REQUIRE(aq.getClauseList()[0].get()->getArgumentList()[0]->getValue() == "a");
        REQUIRE(aq.getClauseList()[0].get()->getArgumentList()[1]->getValue() == "");
        REQUIRE(aq.getClauseList()[1].get()->getArgumentList()[0]->getValue() == "b");
        REQUIRE(aq.getClauseList()[1].get()->getArgumentList()[1]->getValue() == "d");
        REQUIRE(aq.getClauseList()[2].get()->getArgumentList()[0]->getValue() == "c");
        REQUIRE(aq.getClauseList()[2].get()->getArgumentList()[1]->getValue() == "x");
    };
}

TEST_CASE("QPS Next Parser Tests") {
    SECTION(
        "Valid PQL query, ideal query"
        "procedure a;"
        "Select a such that Next(1, 2)"
    ) {
        std::vector<Token> tokens = {
            IdentityToken("procedure"), IdentityToken("a"),
            PunctuationToken(";"), IdentityToken("Select"),
            IdentityToken("a"), IdentityToken("such"),
            IdentityToken("that"), IdentityToken("Next"),
            PunctuationToken("("), NumberToken("1"),
            PunctuationToken(","), NumberToken("2"),
            PunctuationToken(")")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::OK);
        REQUIRE(aq.getSelectionList().size() == 1);
        REQUIRE(aq.getSelectionList()[0]->getValue() == "a");
        REQUIRE(aq.getClauseList().size() == 1);
        std::string test = aq.getClauseList()[0].get()->getArgumentList()[0]->getValue();
        std::string test2 = aq.getClauseList()[0].get()->getArgumentList()[1]->getValue();
        REQUIRE(test == "1");
        REQUIRE(test2 == "2");
    };
    SECTION(
        "Valid PQL query, ideal query"
        "variable a;"
        "Select a such that Parent(12, a)"
    ) {
        std::vector<Token> tokens = {
            IdentityToken("variable"), IdentityToken("a"),
            PunctuationToken(";"), IdentityToken("Select"),
            IdentityToken("a"), IdentityToken("such"),
            IdentityToken("that"), IdentityToken("Parent"),
            PunctuationToken("("), NumberToken("12"),
            PunctuationToken(","), NumberToken("1"),
            PunctuationToken(")")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::OK);
        REQUIRE(aq.getSelectionList().size() == 1);
        REQUIRE(aq.getSelectionList()[0]->getValue() == "a");
        REQUIRE(aq.getClauseList().size() == 1);
        REQUIRE(aq.getClauseList()[0].get()->getArgumentList()[0]->getValue() == "12");
        REQUIRE(aq.getClauseList()[0].get()->getArgumentList()[1]->getValue() == "1");
    };

    SECTION(
        "Invalid PQL query"
        "stmt a;"
        "Select a such that Next(\"main\", a)"
    ) {
        std::vector<Token> tokens = {
            IdentityToken("stmt"), IdentityToken("a"),
            PunctuationToken(";"), IdentityToken("Select"),
            IdentityToken("a"), IdentityToken("such"),
            IdentityToken("that"), IdentityToken("Next"),
            PunctuationToken("("), PunctuationToken("\""),
            IdentityToken("main"), PunctuationToken("\""),
            PunctuationToken(","), IdentityToken("a"),
            PunctuationToken(")")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        try {
            pm.parse(tokens, aq);
            FAIL("Non-statement passed in as argument!");
        } catch (ParserError pe) {
            REQUIRE(pe.status() == ErrorStatus::SYNTAX);
        }
    };

    SECTION(
        "Invalid PQL query"
        "stmt a;"
        "Select a such that Next*(\"x\", 2)"
    ) {
        std::vector<Token> tokens = {
            IdentityToken("stmt"), IdentityToken("a"),
            PunctuationToken(";"), IdentityToken("Select"),
            IdentityToken("a"), IdentityToken("such"),
            IdentityToken("that"), IdentityToken("Next"),
            PunctuationToken("*"), PunctuationToken("("),
            PunctuationToken("\""), IdentityToken("x"),
            PunctuationToken("\""), PunctuationToken(","),
            NumberToken("2"), PunctuationToken(")")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        try {
            pm.parse(tokens, aq);
            FAIL("Non-statement passed in as argument!");
        } catch (ParserError pe) {
            REQUIRE(pe.status() == ErrorStatus::SYNTAX);
        }
    };

    SECTION(
        "Valid PQL query, ideal query"
        "stmt a; procedure p;"
        "Select a such that Next(p, a)"
    ) {
        std::vector<Token> tokens = {
            IdentityToken("stmt"), IdentityToken("a"),
            PunctuationToken(";"), IdentityToken("procedure"), IdentityToken("p"),
            PunctuationToken(";"), IdentityToken("Select"),
            IdentityToken("a"), IdentityToken("such"),
            IdentityToken("that"), IdentityToken("Next"),
            PunctuationToken("("), IdentityToken("p"),
            PunctuationToken(","), IdentityToken("a"),
            PunctuationToken(")")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::SEMANTIC);
    };

    SECTION(
        "Valid PQL query, ideal query"
        "while a; if ifs;"
        "Select a such that Next(a, ifs)"
    ) {
        std::vector<Token> tokens = {
            IdentityToken("while"), IdentityToken("a"),
            PunctuationToken(";"), IdentityToken("if"), IdentityToken("ifs"),
            PunctuationToken(";"), IdentityToken("Select"),
            IdentityToken("a"), IdentityToken("such"),
            IdentityToken("that"), IdentityToken("Next"), PunctuationToken("*"),
            PunctuationToken("("), IdentityToken("a"),
            PunctuationToken(","), IdentityToken("ifs"),
            PunctuationToken(")")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::OK);
        REQUIRE(aq.getSelectionList().size() == 1);
        REQUIRE(aq.getSelectionList()[0]->getValue() == "a");
        REQUIRE(aq.getClauseList().size() == 1);
        REQUIRE(aq.getClauseList()[0].get()->getArgumentList()[0]->getValue() == "a");
        REQUIRE(aq.getClauseList()[0].get()->getArgumentList()[1]->getValue() == "ifs");
    };

    SECTION(
        "Valid PQL query, ideal query"
        "while a; if ifs;"
        "Select a such that Next(a, _)"
    ) {
        std::vector<Token> tokens = {
            IdentityToken("while"), IdentityToken("a"),
            PunctuationToken(";"), IdentityToken("if"), IdentityToken("ifs"),
            PunctuationToken(";"), IdentityToken("Select"),
            IdentityToken("a"), IdentityToken("such"),
            IdentityToken("that"), IdentityToken("Next"),
            PunctuationToken("*"),
            PunctuationToken("("), IdentityToken("a"),
            PunctuationToken(","), PunctuationToken("_"),
            PunctuationToken(")")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::OK);
        REQUIRE(aq.getSelectionList().size() == 1);
        REQUIRE(aq.getSelectionList()[0]->getValue() == "a");
        REQUIRE(aq.getClauseList().size() == 1);
        REQUIRE(aq.getClauseList()[0].get()->getArgumentList()[0]->getValue() == "a");
        REQUIRE(WildcardEntity::checkInstance(aq.getClauseList()[0].get()->getArgumentList()[1].get()));
    };
}

TEST_CASE("QPS Affects Parser Tests") {
    SECTION(
            "Valid PQL query, ideal query"
            "procedure a;"
            "Select a such that Affects(1, 2)"
    ) {
        std::vector<Token> tokens = {
                IdentityToken("procedure"), IdentityToken("a"),
                PunctuationToken(";"), IdentityToken("Select"),
                IdentityToken("a"), IdentityToken("such"),
                IdentityToken("that"), IdentityToken("Affects"),
                PunctuationToken("("), NumberToken("1"),
                PunctuationToken(","), NumberToken("2"),
                PunctuationToken(")")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::OK);
        REQUIRE(aq.getSelectionList().size() == 1);
        REQUIRE(aq.getSelectionList()[0]->getValue() == "a");
        REQUIRE(aq.getClauseList().size() == 1);
        std::string test = aq.getClauseList()[0].get()->getArgumentList()[0]->getValue();
        std::string test2 = aq.getClauseList()[0].get()->getArgumentList()[1]->getValue();
        REQUIRE(test == "1");
        REQUIRE(test2 == "2");
    };
    SECTION(
            "Valid PQL query, ideal query"
            "assign a;"
            "Select a such that Affects(12, a)"
    ) {
        std::vector<Token> tokens = {
                IdentityToken("assign"), IdentityToken("a"),
                PunctuationToken(";"), IdentityToken("Select"),
                IdentityToken("a"), IdentityToken("such"),
                IdentityToken("that"), IdentityToken("Affects"),
                PunctuationToken("("), NumberToken("12"),
                PunctuationToken(","), NumberToken("a"),
                PunctuationToken(")")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::OK);
        REQUIRE(aq.getSelectionList().size() == 1);
        REQUIRE(aq.getSelectionList()[0]->getValue() == "a");
        REQUIRE(aq.getClauseList().size() == 1);
        REQUIRE(aq.getClauseList()[0].get()->getArgumentList()[0]->getValue() == "12");
        REQUIRE(aq.getClauseList()[0].get()->getArgumentList()[1]->getValue() == "a");
    };

    SECTION(
            "Valid PQL query, ideal query"
            "stmt a;"
            "Select a such that Affects(a, 12)"
    ) {
        std::vector<Token> tokens = {
                IdentityToken("stmt"), IdentityToken("a"),
                PunctuationToken(";"), IdentityToken("Select"),
                IdentityToken("a"), IdentityToken("such"),
                IdentityToken("that"), IdentityToken("Affects"),
                PunctuationToken("("), NumberToken("a"),
                PunctuationToken(","), NumberToken("12"),
                PunctuationToken(")")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::OK);
        REQUIRE(aq.getSelectionList().size() == 1);
        REQUIRE(aq.getSelectionList()[0]->getValue() == "a");
        REQUIRE(aq.getClauseList().size() == 1);
        REQUIRE(aq.getClauseList()[0].get()->getArgumentList()[0]->getValue() == "a");
        REQUIRE(aq.getClauseList()[0].get()->getArgumentList()[1]->getValue() == "12");
    };

    SECTION(
            "Invalid PQL query"
            "while a;"
            "Select a such that Affects(_, _)"
    ) {
        std::vector<Token> tokens = {
                IdentityToken("while"), IdentityToken("a"),
                PunctuationToken(";"), IdentityToken("Select"),
                IdentityToken("a"), IdentityToken("such"),
                IdentityToken("that"), IdentityToken("Affects"),
                PunctuationToken("("), PunctuationToken("_"),
                PunctuationToken(","), PunctuationToken("_"),
                PunctuationToken(")")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::OK);
        REQUIRE(aq.getSelectionList().size() == 1);
        REQUIRE(aq.getSelectionList()[0]->getValue() == "a");
        REQUIRE(aq.getClauseList().size() == 1);
        REQUIRE(WildcardEntity::checkInstance(aq.getClauseList()[0].get()->getArgumentList()[0].get()));
        REQUIRE(WildcardEntity::checkInstance(aq.getClauseList()[0].get()->getArgumentList()[1].get()));
    };

    SECTION(
            "Invalid PQL query"
            "procedure a;"
            "Select a such that Affects*(a, \"hi\")"
    ) {
        std::vector<Token> tokens = {
                IdentityToken("procedure"), IdentityToken("a"),
                PunctuationToken(";"), IdentityToken("Select"),
                IdentityToken("a"), IdentityToken("such"),
                IdentityToken("that"), IdentityToken("Affects"),
                PunctuationToken("*"), PunctuationToken("("),
                IdentityToken("a"), PunctuationToken(","),
                PunctuationToken("\""), IdentityToken("hi"),
                PunctuationToken("\""), PunctuationToken(")")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        try {
            pm.parse(tokens, aq);
            FAIL("Non-stmtRef passed in as argument!");
        } catch (ParserError pe) {
            REQUIRE(aq.getQueryStatus() == ErrorStatus::SEMANTIC);
            REQUIRE(pe.status() == ErrorStatus::SYNTAX);
        }
    };


    SECTION(
            "read a; assign p;"
            "Select a such that Affects*(p, a)"
    ) {
        std::vector<Token> tokens = {
                IdentityToken("read"), IdentityToken("a"),
                PunctuationToken(";"), IdentityToken("assign"), IdentityToken("p"),
                PunctuationToken(";"), IdentityToken("Select"),
                IdentityToken("a"), IdentityToken("such"),
                IdentityToken("that"), IdentityToken("Affects"),
                PunctuationToken("*"),
                PunctuationToken("("), IdentityToken("p"),
                PunctuationToken(","), IdentityToken("a"),
                PunctuationToken(")")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::OK);
        REQUIRE(aq.getSelectionList().size() == 1);
        REQUIRE(aq.getSelectionList()[0]->getValue() == "a");
        REQUIRE(aq.getClauseList().size() == 1);
        REQUIRE(aq.getClauseList()[0].get()->getArgumentList()[0]->getValue() == "p");
        REQUIRE(aq.getClauseList()[0].get()->getArgumentList()[1]->getValue() == "a");
    };

    SECTION(
            "while a; if ifs;"
            "Select a such that Affects*(_, 1)"
    ) {
        std::vector<Token> tokens = {
                IdentityToken("while"), IdentityToken("a"),
                PunctuationToken(";"), IdentityToken("if"), IdentityToken("ifs"),
                PunctuationToken(";"), IdentityToken("Select"),
                IdentityToken("a"), IdentityToken("such"),
                IdentityToken("that"), IdentityToken("Affects"), PunctuationToken("*"),
                PunctuationToken("("), PunctuationToken("_"),
                PunctuationToken(","), NumberToken("1"),
                PunctuationToken(")")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::OK);
        REQUIRE(aq.getSelectionList().size() == 1);
        REQUIRE(aq.getSelectionList()[0]->getValue() == "a");
        REQUIRE(aq.getClauseList().size() == 1);
        REQUIRE(WildcardEntity::checkInstance(aq.getClauseList()[0].get()->getArgumentList()[0].get()));
        REQUIRE(aq.getClauseList()[0].get()->getArgumentList()[1]->getValue() == "1");
    };

    SECTION(
            "while a; if ifs;"
            "Select a such that Affects(a, _)"
    ) {
        std::vector<Token> tokens = {
                IdentityToken("assign"), IdentityToken("a"),
                PunctuationToken(";"), IdentityToken("if"), IdentityToken("ifs"),
                PunctuationToken(";"), IdentityToken("Select"),
                IdentityToken("ifs"), IdentityToken("such"),
                IdentityToken("that"), IdentityToken("Affects"),
                PunctuationToken("("), IdentityToken("a"),
                PunctuationToken(","), PunctuationToken("_"),
                PunctuationToken(")")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::OK);
        REQUIRE(aq.getSelectionList().size() == 1);
        REQUIRE(aq.getSelectionList()[0]->getValue() == "ifs");
        REQUIRE(aq.getClauseList().size() == 1);
        REQUIRE(aq.getClauseList()[0].get()->getArgumentList()[0]->getValue() == "a");
        REQUIRE(WildcardEntity::checkInstance(aq.getClauseList()[0].get()->getArgumentList()[1].get()));
    };

    SECTION(
            "procedure a; assign p; assign stmt;"
            "Select a such that Affects*(p, a) and Affects(stmt, p) and Affects(\"oops\", _)"
    ) {
        std::vector<Token> tokens = {
                IdentityToken("procedure"), IdentityToken("a"),
                PunctuationToken(";"), IdentityToken("assign"), IdentityToken("p"),
                PunctuationToken(";"), IdentityToken("assign"), IdentityToken("stmt"),
                PunctuationToken(";"), IdentityToken("Select"),
                IdentityToken("a"), IdentityToken("such"),
                IdentityToken("that"), IdentityToken("Affects"),
                PunctuationToken("*"),
                PunctuationToken("("), IdentityToken("p"),
                PunctuationToken(","), IdentityToken("a"),
                PunctuationToken(")"), IdentityToken("and"), IdentityToken("Affects"),
                PunctuationToken("("), IdentityToken("stmt"),
                PunctuationToken(","), IdentityToken("p"),
                PunctuationToken(")"), IdentityToken("and"), IdentityToken("Affects"),
                PunctuationToken("("), PunctuationToken("\""), IdentityToken("oops"),
                PunctuationToken("\""),
                PunctuationToken(","), PunctuationToken("_"),
                PunctuationToken(")"),
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        try {
            pm.parse(tokens, aq);
            FAIL("Should throw SYNTAX ERROR!!");
        } catch (ParserError pe) {
            REQUIRE(aq.getQueryStatus() == ErrorStatus::SEMANTIC);
            REQUIRE(pe.status() == ErrorStatus::SYNTAX);
        }
    };

    SECTION(
            "stmt s; print p;"
            "Select s such that Affects*(s, p)"
    ) {
        std::vector<Token> tokens = {
                IdentityToken("stmt"), IdentityToken("s"),
                PunctuationToken(";"), IdentityToken("print"), IdentityToken("p"),
                PunctuationToken(";"), IdentityToken("Select"),
                IdentityToken("s"), IdentityToken("such"),
                IdentityToken("that"), IdentityToken("Affects"),
                PunctuationToken("*"),
                PunctuationToken("("), IdentityToken("s"),
                PunctuationToken(","), IdentityToken("p"),
                PunctuationToken(")")
        };
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::OK);
        REQUIRE(aq.getSelectionList().size() == 1);
        REQUIRE(aq.getSelectionList()[0]->getValue() == "s");
        REQUIRE(aq.getClauseList().size() == 1);
        REQUIRE(aq.getClauseList()[0].get()->getArgumentList()[0]->getValue() == "s");
        REQUIRE(aq.getClauseList()[0].get()->getArgumentList()[1]->getValue() == "p");
    }
}
