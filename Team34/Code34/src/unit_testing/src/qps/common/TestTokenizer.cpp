//
// Created by Ryan Low on 1/2/23.
//
#include "catch.hpp"
#include "common/tokenizer/Tokenizer.h"
#include "common/tokenizer/IdentityToken.h"
#include "common/tokenizer/PunctuationToken.h"

TEST_CASE("QPS tokenizer Tests") {
    SECTION(
            "Valid PQL query"
            "variable a, b;"
            "Select a"
    ) {
        std::string query = "variable a, b;"
                            "Select a";
        Tokenizer tokenizer;
        tokenizer.tokenize(query);
        std::vector<Token> tokens = tokenizer.getTokens();
        std::vector<Token> expectedTokens = std::vector<Token>({
               IdentityToken("variable"), IdentityToken("a"), PunctuationToken(","),
               IdentityToken("b"), PunctuationToken(";"), IdentityToken("Select"),
               IdentityToken("a")
       });
        REQUIRE(std::equal(begin(tokens), end(tokens),
                           begin(expectedTokens), end(expectedTokens),
                           [](const Token& token1, const Token& token2) {
                               return token1 == token2;
                           }));
        REQUIRE(!tokenizer.hasError());
    }

    SECTION(
            "Invalid PQL query because of invalid character."
            "variable a, b;"
            "Select ç"
    ) {
        std::string query = "variable a, b;"
                            "Select ç";
        Tokenizer tokenizer;
        tokenizer.tokenize(query);
        std::vector<Token> tokens = tokenizer.getTokens();
        REQUIRE(tokenizer.hasError());
    }

    SECTION(
            "Tokenize empty std::string."
            " "
    ) {
        std::string query = " ";
        Tokenizer tokenizer;
        tokenizer.tokenize(query);
        std::vector<Token> tokens = tokenizer.getTokens();
        REQUIRE(tokens.empty());
        REQUIRE(!tokenizer.hasError());
    }

}

TEST_CASE("SIMPLE tokenizer Tests") {
    SECTION(
        "Valid SIMPLE program"
        "procedure example { read x; read y; }"
    ) {
        std::string simple = "procedure example { read x; read y; }";
        Tokenizer tokenizer;
        tokenizer.tokenize(simple);
        std::vector<Token> tokens = tokenizer.getTokens();
        std::vector<Token> expectedTokens = std::vector<Token>({
            IdentityToken("procedure"), IdentityToken("example"), PunctuationToken("{"),
            IdentityToken("read"), IdentityToken("x"), PunctuationToken(";"),
            IdentityToken("read"), IdentityToken("y"), PunctuationToken(";"), 
            PunctuationToken("}")
            });
        REQUIRE(std::equal(begin(tokens), end(tokens),
            begin(expectedTokens), end(expectedTokens),
            [](const Token& token1, const Token& token2) {
                return token1 == token2;
            }));
        REQUIRE(!tokenizer.hasError());
    }

    SECTION(
        "Invalid SIMPLE program because of invalid character."
        "procedure example2 { read ç; print ç; }"
    ) {
        std::string query = "procedure example2 { read ç; print ç; }";
        Tokenizer tokenizer;
        tokenizer.tokenize(query);
        std::vector<Token> tokens = tokenizer.getTokens();
        REQUIRE(tokenizer.hasError());
    }

    SECTION(
            "Valid simple program with leading 0s."
            "Select BOOLEAN with \"x\" = 000"
    ) {
        std::string query = "Select BOOLEAN with \"x\" = 000";
        Tokenizer tokenizer;
        tokenizer.tokenize(query);
        std::vector<Token> tokens = tokenizer.getTokens();
        REQUIRE(tokenizer.hasError());
    }
    SECTION(
            "Select BOOLEAN with 01 = 1"
    ) {
        std::string query = "Select BOOLEAN with 01 = 1";
        Tokenizer tokenizer;
        tokenizer.tokenize(query);
        std::vector<Token> tokens = tokenizer.getTokens();
        REQUIRE(tokenizer.hasError());
    }


    SECTION(
            "assign a; Select BOOLEAN pattern a(\"x\", \"y + 09\")"
    ) {
        std::string query = "assign a; Select BOOLEAN pattern a(\"x\", \"y + 09\")";
        Tokenizer tokenizer;
        tokenizer.tokenize(query);
        std::vector<Token> tokens = tokenizer.getTokens();
        REQUIRE(tokenizer.hasError());
    }
    SECTION(
            "assign a; Select a such that Follows(01, 20)"
    ) {
        std::string query = "assign a; Select a such that Follows(01, 20)";
        Tokenizer tokenizer;
        tokenizer.tokenize(query);
        std::vector<Token> tokens = tokenizer.getTokens();
        REQUIRE(tokenizer.hasError());
    }

    SECTION(
        "assign a; Select a with 1 = 01 1"
    ) {
        std::string query = "assign a; Select a with 1 = 01 1";
        Tokenizer tokenizer;
        tokenizer.tokenize(query);
        std::vector<Token> tokens = tokenizer.getTokens();
        REQUIRE(tokenizer.hasError());
    }

    SECTION(
            "assign a; Select a with 1 = 1 01"
    ) {
        std::string query = "assign a; Select a with 1 = 1 01";
        Tokenizer tokenizer;
        tokenizer.tokenize(query);
        std::vector<Token> tokens = tokenizer.getTokens();
        REQUIRE(tokenizer.hasError());
    }
}