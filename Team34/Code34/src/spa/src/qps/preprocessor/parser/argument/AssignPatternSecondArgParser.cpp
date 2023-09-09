// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "AssignPatternSecondArgParser.h"
#include "common/exceptions/ErrorStatus.h"
#include "common/exceptions/ParserError.h"
#include "qps/argument/entity/WildcardEntity.h"
#include "qps/preprocessor/parser/argument/ExpressionParser.h"

AssignPatternSecondArgParser::AssignPatternSecondArgParser() : ArgumentParser() {}

ArgumentResult AssignPatternSecondArgParser::parse(std::vector<Token> tokens,
    std::unordered_map<std::string, std::shared_ptr<EntityArgument>> declarations,
    int pos) {
    Token nextToken = tokens[pos];
    if (isQuotation(nextToken)) {
        return ExpressionParser(false).parse(tokens, declarations, pos);
    } else if (isWildcard(nextToken)) {
        pos++;  // consume wildcard entity or partial left wildcard
        nextToken = tokens[pos];
        if (nextToken.getValue() == ")") {
            return {std::make_shared<WildcardEntity>(), pos, ErrorStatus::OK};
        } else if (isQuotation(nextToken)) {
            return ExpressionParser(true).parse(tokens, declarations, pos);
        } else {
            throw ParserError(ErrorStatus::SYNTAX);
        }
    } else {
        throw ParserError(ErrorStatus::SYNTAX);
    }
}
