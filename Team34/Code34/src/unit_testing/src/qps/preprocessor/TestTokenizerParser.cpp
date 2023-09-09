//
// Created by Ryan Low on 5/2/23.
//
#include "catch.hpp"
#include "common/tokenizer/Tokenizer.h"
#include "qps/preprocessor/parser/ParserManager.h"

TEST_CASE("Ms2 bugs") {
    SECTION(
    "while w; variable v; Select w such that Modifies(w, v) with v.varName = \"x\""
    ) {
        std::string query = "while w; variable v; Select w such that Modifies(w, v) with v.varName = \"x\"";
        std::vector<Token> tokens = Tokenizer().tokenize(query);
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::OK);
        REQUIRE(aq.getSelectionList().size() == 1);
        REQUIRE(aq.getSelectionList()[0]->getValue() == "w");
        REQUIRE(aq.getClauseList().size() == 2);
        REQUIRE(aq.getClauseList()[0].get()->getArgumentList()[0]->getValue() == "w");
        REQUIRE(aq.getClauseList()[0].get()->getArgumentList()[1]->getValue() == "v");
        REQUIRE(aq.getClauseList()[1].get()->getArgumentList()[0]->getValue() == "v");
        REQUIRE(aq.getClauseList()[1].get()->getArgumentList()[1]->getValue() == "x");
    }

    SECTION(
    "if ifs; variable v; Select v such that Uses (ifs, v) with ifs.stmt# 22"
    ) {
        std::string query = "if ifs; variable v; Select v such that Uses (ifs, v) with ifs.stmt# = 22";
        std::vector<Token> tokens = Tokenizer().tokenize(query);
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::OK);
        REQUIRE(aq.getSelectionList().size() == 1);
        REQUIRE(aq.getSelectionList()[0]->getValue() == "v");
        REQUIRE(aq.getClauseList().size() == 2);
        REQUIRE(aq.getClauseList()[0].get()->getArgumentList()[0]->getValue() == "ifs");
        REQUIRE(aq.getClauseList()[0].get()->getArgumentList()[1]->getValue() == "v");
        REQUIRE(aq.getClauseList()[1].get()->getArgumentList()[0]->getValue() == "ifs");
        REQUIRE(aq.getClauseList()[1].get()->getArgumentList()[1]->getValue() == "22");
    }

    SECTION(
    "if ifs; variable v; Select v such that Uses (ifs, v) with ifs.stmt# 22"
    ) {
        std::string query = "if ifs; variable v; Select v such that Uses (ifs, v) with ifs.stmt# = 22";
        std::vector<Token> tokens = Tokenizer().tokenize(query);
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::OK);
        REQUIRE(aq.getSelectionList().size() == 1);
        REQUIRE(aq.getSelectionList()[0]->getValue() == "v");
        REQUIRE(aq.getClauseList().size() == 2);
        REQUIRE(aq.getClauseList()[0].get()->getArgumentList()[0]->getValue() == "ifs");
        REQUIRE(aq.getClauseList()[0].get()->getArgumentList()[1]->getValue() == "v");
        REQUIRE(aq.getClauseList()[1].get()->getArgumentList()[0]->getValue() == "ifs");
        REQUIRE(aq.getClauseList()[1].get()->getArgumentList()[1]->getValue() == "22");
    }

    SECTION(
    "procedure p, q; Select BOOLEAN such that Calls (p, q) with q.procName = \"p\" and p.procName = \"Example\""
    ) {
        std::string query = "procedure p, q; Select BOOLEAN such that Calls (p, q) with q.procName = \"p\" and p.procName = \"Example\"";
        std::vector<Token> tokens = Tokenizer().tokenize(query);
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::OK);
        REQUIRE(aq.getSelectionList().size() == 0);
        REQUIRE(aq.getSelectBoolean());
        REQUIRE(aq.getClauseList().size() == 3);
        REQUIRE(aq.getClauseList()[0].get()->getArgumentList()[0]->getValue() == "p");
        REQUIRE(aq.getClauseList()[0].get()->getArgumentList()[1]->getValue() == "q");
        REQUIRE(aq.getClauseList()[1].get()->getArgumentList()[0]->getValue() == "q");
        REQUIRE(aq.getClauseList()[1].get()->getArgumentList()[1]->getValue() == "p");
        REQUIRE(aq.getClauseList()[2].get()->getArgumentList()[0]->getValue() == "p");
        REQUIRE(aq.getClauseList()[2].get()->getArgumentList()[1]->getValue() == "Example");
    }

    SECTION(
        "procedure p, q; Select BOOLEAN such that Calls (p, q) with q.procName = \"p\" and p.procName = \"Example\""
        ) {
        std::string query = "procedure p, q; Select BOOLEAN such that Calls (p, q) with q.procName = \"p\" and p.procName = \"Example\"";
        std::vector<Token> tokens = Tokenizer().tokenize(query);
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::OK);
        REQUIRE(aq.getSelectionList().size() == 0);
        REQUIRE(aq.getSelectBoolean());
        REQUIRE(aq.getClauseList().size() == 3);
        REQUIRE(aq.getClauseList()[0].get()->getArgumentList()[0]->getValue() == "p");
        REQUIRE(aq.getClauseList()[0].get()->getArgumentList()[1]->getValue() == "q");
        REQUIRE(aq.getClauseList()[1].get()->getArgumentList()[0]->getValue() == "q");
        REQUIRE(aq.getClauseList()[1].get()->getArgumentList()[1]->getValue() == "p");
        REQUIRE(aq.getClauseList()[2].get()->getArgumentList()[0]->getValue() == "p");
        REQUIRE(aq.getClauseList()[2].get()->getArgumentList()[1]->getValue() == "Example");
    }

    SECTION(
            "constant torture; Select torture with torture.value = -1"
    ) {
        std::string query = "constant torture; Select torture with torture.value = -1";
        std::vector<Token> tokens = Tokenizer().tokenize(query);
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        try {
            pm.parse(tokens, aq);
            FAIL("Should throw syntax error from negative number");
        } catch (ParserError pe) {
            REQUIRE(pe.status() == ErrorStatus::SYNTAX);
        }
    }

    SECTION(
            "assign a; Select a pattern a(\"x1\",_,_)"
    ) {
        std::string query = "assign a; Select a pattern a(\"x1\",_,_)";
        std::vector<Token> tokens = Tokenizer().tokenize(query);
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::SEMANTIC);
    }

    SECTION(
            "while w; Select w pattern w(\"1a\", _)"
            ) {
        std::string query = "while w; Select w pattern w(\"10\", _)";
        std::vector<Token> tokens = Tokenizer().tokenize(query);
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        try {
            pm.parse(tokens, aq);
            FAIL("Should throw syntax error from non IDENT");
        } catch (ParserError pe) {
            REQUIRE(pe.status() == ErrorStatus::SYNTAX);
        }
    }
    SECTION(
            "stmt s; Select s such that Modifies(_, _)"
    ) {
        std::string query = "stmt s; Select s such that Modifies(_, _)";
        std::vector<Token> tokens = Tokenizer().tokenize(query);
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::SEMANTIC);
    }
    SECTION(
            "assign a; Select a pattern b(_, _,_)"
    ) {
        std::string query = "assign a; stmt s; Select a pattern s (\"nat\", \"nat + 1\")";
        std::vector<Token> tokens = Tokenizer().tokenize(query);
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::SEMANTIC);
    }
    SECTION(
            "while w; Select w pattern w(\"10\", _)"
    ) {
        std::string query = "while w; Select w pattern w(\"10\", _)";
        std::vector<Token> tokens = Tokenizer().tokenize(query);
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        try {
            pm.parse(tokens, aq);
        } catch (ParserError pe) {
            REQUIRE(pe.status() == ErrorStatus::SYNTAX);
        }
    }
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
    }
    SECTION(
            "procedure p; constant const; Select p with proc.procName = const.value"
    ) {
        std::string query = "procedure p; constant const; ";
        query += "Select p with proc.procName = const.value";
        std::vector<Token> tokens = Tokenizer().tokenize(query);
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::SEMANTIC);
    }
    SECTION(
            "assign a; variable v; Select a such that "
            "Uses(a1, v) pattern a (v, _\"ryan + 5\"_)"
    ) {
        std::string query = "assign a; variable v; Select a such that ";
        query += "Uses(a1, v) pattern a (v, _\"ryan + 5\"_)";
        std::vector<Token> tokens = Tokenizer().tokenize(query);
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::SEMANTIC);
    }
    SECTION(
            "procedure P; call C; while w; Select p such that Calls (\"Monkey\", p) and Parent (w, c) with c. procName = p. procName"
    ) {
        std::string query = "procedure p; call c; while w; Select p such that Calls (\"Monkey\", p) and Parent (w, c) with c.procName = p.procName";
        std::vector<Token> tokens = Tokenizer().tokenize(query);
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::OK);
        REQUIRE(aq.getSelectionList().size() == 1);
        REQUIRE(aq.getClauseList().size() == 3);
        REQUIRE(aq.getClauseList()[0].get()->getArgumentList()[0]->getValue() == "Monkey");
        REQUIRE(aq.getClauseList()[0].get()->getArgumentList()[1]->getValue() == "p");
        REQUIRE(aq.getClauseList()[1].get()->getArgumentList()[0]->getValue() == "w");
        REQUIRE(aq.getClauseList()[1].get()->getArgumentList()[1]->getValue() == "c");
        REQUIRE(aq.getClauseList()[2].get()->getArgumentList()[0]->getValue() == "c");
        REQUIRE(aq.getClauseList()[2].get()->getArgumentList()[1]->getValue() == "p");
    }
    SECTION(
            "while w; Select w pattern w(_,_,_)"
    ) {
        std::string query = "while w; Select w pattern w(_,_,_)";
        std::vector<Token> tokens = Tokenizer().tokenize(query);
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::SEMANTIC);
    }

    SECTION(
            "while w; Select w pattern w(\"xxx\", _)"
    ) {
        std::string query = "while w; Select w pattern w(\"xxx\", _)";
        std::vector<Token> tokens = Tokenizer().tokenize(query);
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::OK);
        REQUIRE(aq.getSelectionList().size() == 1);
        REQUIRE(aq.getClauseList().size() == 1);
        REQUIRE(aq.getClauseList()[0].get()->getArgumentList()[0]->getValue() == "w");
        REQUIRE(aq.getClauseList()[0].get()->getArgumentList()[1]->getValue() == "xxx");
    }


    SECTION(
            "stmt a; procedure p; Select a such that Next(p, a)"
    ) {
        std::string query = "stmt a; procedure p; Select a such that Next(p, a)";
        std::vector<Token> tokens = Tokenizer().tokenize(query);
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::SEMANTIC);
    }
    SECTION(
            "call cl; Select cl with cl.procName = \"aram\" and \"aram\" = cl.procName"
    ) {
        std::string query = "call cl; Select cl with cl.procName = \"aram\" and \"aram\" = cl.procName";
        std::vector<Token> tokens = Tokenizer().tokenize(query);
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::OK);
        REQUIRE(aq.getSelectionList().size() == 1);
        REQUIRE(aq.getClauseList().size() == 2);
        REQUIRE(aq.getClauseList()[0].get()->getArgumentList()[0]->getValue() == "cl");
        REQUIRE(aq.getClauseList()[0].get()->getArgumentList()[1]->getValue() == "aram");
        REQUIRE(aq.getClauseList()[1].get()->getArgumentList()[0]->getValue() == "aram");
        REQUIRE(aq.getClauseList()[1].get()->getArgumentList()[1]->getValue() == "cl");
    }

    SECTION(
            "call cl; procedure p, p1; Select cl such that Calls(p, p1) with p.procName = cl.procName"
    ) {
        std::string query = "call cl; procedure p, p1; Select cl such that Calls(p, p1) with p.procName = cl.procName";
        std::vector<Token> tokens = Tokenizer().tokenize(query);
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::OK);
        REQUIRE(aq.getSelectionList().size() == 1);
        REQUIRE(aq.getClauseList().size() == 2);
        REQUIRE(aq.getClauseList()[0].get()->getArgumentList()[0]->getValue() == "p");
        REQUIRE(aq.getClauseList()[0].get()->getArgumentList()[1]->getValue() == "p1");
        REQUIRE(aq.getClauseList()[1].get()->getArgumentList()[0]->getValue() == "p");
        REQUIRE(aq.getClauseList()[1].get()->getArgumentList()[1]->getValue() == "cl");
    }
    SECTION(
            "stmt s; Select s such that Follows(s, s)"
    ) {
        std::string query = "stmt s; Select s such that Follows(s, s)";
        std::vector<Token> tokens = Tokenizer().tokenize(query);
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::OK);
        REQUIRE(aq.getSelectionList().size() == 1);
        REQUIRE(aq.getClauseList().size() == 1);
        REQUIRE(aq.getClauseList()[0].get()->getArgumentList()[0]->getValue() == "s");
        REQUIRE(aq.getClauseList()[0].get()->getArgumentList()[1]->getValue() == "s");
    }
    SECTION(
            "Select BOOLEAN such that Affects(2, 3) and Affects(2, 5) and Affects (18, 19)"
    ) {
        std::string query = "Select BOOLEAN such that Affects(2, 3) and Affects(2, 5) and Affects (18, 19)";
        std::vector<Token> tokens = Tokenizer().tokenize(query);
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::OK);
        REQUIRE(aq.getSelectionList().empty());
        REQUIRE(aq.getSelectBoolean());
        REQUIRE(aq.getClauseList().size() == 3);
        REQUIRE(aq.getClauseList()[0].get()->getArgumentList()[0]->getValue() == "2");
        REQUIRE(aq.getClauseList()[0].get()->getArgumentList()[1]->getValue() == "3");
        REQUIRE(aq.getClauseList()[1].get()->getArgumentList()[0]->getValue() == "2");
        REQUIRE(aq.getClauseList()[1].get()->getArgumentList()[1]->getValue() == "5");
        REQUIRE(aq.getClauseList()[2].get()->getArgumentList()[0]->getValue() == "18");
        REQUIRE(aq.getClauseList()[2].get()->getArgumentList()[1]->getValue() == "19");
    }
    SECTION(
            "stmt s; Select s such that Affects*(s, 13)"
    ) {
        std::string query = "stmt s; Select s such that Affects*(s, 13)";
        std::vector<Token> tokens = Tokenizer().tokenize(query);
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::OK);
        REQUIRE(aq.getSelectionList().size() == 1);
        REQUIRE(aq.getSelectionList()[0]->getValue() == "s");
        REQUIRE(aq.getClauseList().size() == 1);
        REQUIRE(aq.getClauseList()[0].get()->getArgumentList()[0]->getValue() == "s");
        REQUIRE(aq.getClauseList()[0].get()->getArgumentList()[1]->getValue() == "13");
    }
    SECTION(
            "while such; assign that; variable with; Select such such that Parent* (such, that) pattern that (with, _) with with.varName = \"Select\""
    ) {
        std::string query = "while such; assign that; variable with; Select such such that Parent* "
                            "(such, that) pattern that (with, _) with with.varName = \"Select\"";
        std::vector<Token> tokens = Tokenizer().tokenize(query);
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::OK);
        REQUIRE(aq.getSelectionList().size() == 1);
        REQUIRE(aq.getSelectionList()[0]->getValue() == "such");
        REQUIRE(aq.getClauseList().size() == 3);
        REQUIRE(aq.getClauseList()[0].get()->getArgumentList()[0]->getValue() == "such");
        REQUIRE(aq.getClauseList()[0].get()->getArgumentList()[1]->getValue() == "that");
        REQUIRE(aq.getClauseList()[1].get()->getArgumentList()[0]->getValue() == "that");
        REQUIRE(aq.getClauseList()[1].get()->getArgumentList()[1]->getValue() == "with");
        REQUIRE(aq.getClauseList()[2].get()->getArgumentList()[0]->getValue() == "with");
        REQUIRE(aq.getClauseList()[2].get()->getArgumentList()[1]->getValue() == "Select");
    }
    SECTION(
            "Select BOOLEAN with 12=12 and"
    ) {
        std::string query = "Select BOOLEAN with 12=12 and";
        std::vector<Token> tokens = Tokenizer().tokenize(query);
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        try {
            pm.parse(tokens, aq);
            FAIL("Should be syntax");
        } catch (ParserError pe) {
            REQUIRE(pe.status() == ErrorStatus::SYNTAX);
        }
    }
    SECTION(
            "procedure a; Select a such that Calls(\"A\", p)"
    ) {
        std::string query = "procedure a; Select a such that Calls(\"A\", p)";
        std::vector<Token> tokens = Tokenizer().tokenize(query);
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        pm.parse(tokens, aq);
        REQUIRE(aq.getQueryStatus() == ErrorStatus::SEMANTIC);
    }
    SECTION(
            "Select BOOLEAN with 12=12 and"
    ) {
        std::string query = "Select BOOLEAN with 12=12 and";
        std::vector<Token> tokens = Tokenizer().tokenize(query);
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        try {
            pm.parse(tokens, aq);
            FAIL("Should be syntax");
        } catch (ParserError pe) {
            REQUIRE(pe.status() == ErrorStatus::SYNTAX);
        }
    }
    SECTION(
            "Select BOOLEAN such that"
    ) {
        std::string query = "Select BOOLEAN such that";
        Tokenizer tokenizer;
        tokenizer.tokenize(query);
        std::vector<Token> tokens = tokenizer.getTokens();
        ParserManager pm = ParserManager();
        AbstractQuery aq;
        try {
            pm.parse(tokens, aq);
            FAIL("Should be syntax");
        } catch (ParserError pe) {
            REQUIRE(pe.status() == ErrorStatus::SYNTAX);
        }
    }
}

TEST_CASE("TEST NOW") {
}