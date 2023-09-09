// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "SelectParser.h"

SelectParser::SelectParser() : DeclarationClauseParser() {}

bool SelectParser::isTupleStart(Token token) {
    return token.getValue() == tupleStart;
}

bool SelectParser::isTupleEnd(Token token) {
    return token.getValue() == tupleEnd;
}

void SelectParser::validateTuple(std::vector<std::shared_ptr<Argument>> tuple) {
    if (tuple.size() < 1) {
        throw ParserError(ErrorStatus::SYNTAX);
    }
}

void SelectParser::addAllElemToSelection(AbstractQuery& parsedQuery,
    std::vector<std::shared_ptr<Argument>> tuple) {
    for (std::shared_ptr<Argument> curr : tuple) {
        parsedQuery.addSelection(curr);
    }
}

bool SelectParser::isBooleanDeclared(Token token, std::unordered_map<std::string,
    std::shared_ptr<EntityArgument>> declarations) {
    return declarations.find(token.getValue()) != declarations.end();
}

ParserResult SelectParser::parseTuple(std::vector<Token> tokens, AbstractQuery& parsedQuery,
    std::unordered_map<std::string, std::shared_ptr<EntityArgument>> declarations, int pos) {
    ElementParser elemParser(true);
    pos++;  // consume start tuple
    std::vector<std::shared_ptr<Argument>> tuple;
    ArgumentResult ar = elemParser.parse(tokens, declarations, pos);
    tuple.push_back(ar.getArg());
    pos = ar.getPos();
    while (pos < tokens.size()) {
        if (isTupleEnd(tokens[pos])) {
            pos++;
            validateTuple(tuple);
            addAllElemToSelection(parsedQuery, tuple);
            return {declarations, pos};
        }
        pos += consumeComma(tokens[pos]);
        ar = elemParser.parse(tokens, declarations, pos);
        tuple.push_back(ar.getArg());
        pos = ar.getPos();
        updateIfSemantic(ar.getErrorStatus(), parsedQuery);
    }
    throw ParserError(ErrorStatus::SYNTAX);
}

ParserResult SelectParser::parseBoolean(std::vector<Token> tokens, AbstractQuery& parsedQuery,
    std::unordered_map<std::string, std::shared_ptr<EntityArgument>> declarations, int pos) {
    parsedQuery.setSelectBoolean(true);
    pos++;
    return {declarations, pos};
}

ParserResult SelectParser::parse(std::vector<Token> tokens, AbstractQuery& parsedQuery,
    std::unordered_map<std::string, std::shared_ptr<EntityArgument>> declarations, int pos) {
    pos++;  // consume Select
    if (tokens.size() - pos <= 0) {
        throw ParserError(ErrorStatus::SYNTAX);
    }

    ElementParser elemParser = ElementParser(true);
    if (isTupleStart(tokens[pos])) {
        return parseTuple(tokens, parsedQuery, declarations, pos);
    }

    Token boolOrSingleElem = tokens[pos];
    if (isBoolean(boolOrSingleElem) && !isBooleanDeclared(boolOrSingleElem, declarations)) {
        return parseBoolean(tokens, parsedQuery, declarations, pos);
    }

    ArgumentResult ar = elemParser.parse(tokens, declarations, pos);
    updateIfSemantic(ar.getErrorStatus(), parsedQuery);
    parsedQuery.addSelection(ar.getArg());
    return {declarations, ar.getPos()};
}
