// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "ExpressionParser.h"

ExpressionParser::ExpressionParser(bool isPartial) : isPartial(isPartial), ArgumentParser() {}

std::string ExpressionParser::getExpressionString(std::vector<Token> tokens) {
    std::string result = "";
    for (Token c : tokens) {
        result += c.getValue();
    }
    return result;
}

ArgumentResult ExpressionParser::parse(std::vector<Token> tokens,
    std::unordered_map<std::string, std::shared_ptr<EntityArgument>> declarations, int pos) {
    pos++;  // consume open quote
    Token nextToken = tokens[pos];
    std::vector<Token> expressionTokens;
    while (!isQuotation(nextToken)) {
        if (pos >= tokens.size()) {
            throw ParserError(ErrorStatus::SYNTAX);
        }
        expressionTokens.push_back(nextToken);
        pos++;
        nextToken = tokens[pos];
    }
    pos++;  // consume close quote
    if (isPartial && !isWildcard(tokens[pos])) {
        throw ParserError(ErrorStatus::SYNTAX);
    }

    pos = isPartial ? pos + 1 : pos;

    std::string expressionString = getExpressionString(expressionTokens);
    expressionTokens.insert(expressionTokens.begin(), PunctuationToken("("));
    expressionTokens.insert(expressionTokens.end(), PunctuationToken(")"));
    std::shared_ptr<ExpressionNode> ast = ASTUtil::convertToAST(expressionTokens);

    return {std::make_shared<ExpressionInput>(expressionString, ast, isPartial),
            pos, ErrorStatus::OK};
}
