// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "PatternParser.h"

PatternParser::PatternParser() : DeclarationClauseParser() {
}

std::shared_ptr<DeclarationClauseParser> PatternParser::getParser(std::string synonymType,
    std::shared_ptr<Argument> arg) {
    if (synonymType == IfStmtEntity::TYPE_NAME) {
        return std::make_shared<IfPatternParser>(arg);
    }
    if (synonymType == AssignStmtEntity::TYPE_NAME) {
        return std::make_shared<AssignPatternParser>(arg);
    }
    if (synonymType == WhileStmtEntity::TYPE_NAME) {
        return std::make_shared<WhilePatternParser>(arg);
    }
}

ParserResult PatternParser::checkForSyntaxError(std::vector<Token> tokens,
    AbstractQuery &parsedQuery,
    std::unordered_map<std::string, std::shared_ptr<EntityArgument>> declarations,
    int pos) {
    try {
        AssignPatternParser assignPatternParser =
                AssignPatternParser(std::make_shared<DummyArgument>());
        assignPatternParser.checkForSyntax();
        return assignPatternParser
            .parse(tokens, parsedQuery, declarations, pos);
    } catch (ParserError pe) {
        try {
            IfPatternParser ifPatternParser =
                    IfPatternParser(std::make_shared<DummyArgument>());
            ifPatternParser.checkForSyntax();
            return ifPatternParser
                    .parse(tokens, parsedQuery, declarations, pos);
        } catch (ParserError pe) {
            WhilePatternParser whilePatternParser =
                    WhilePatternParser(std::make_shared<DummyArgument>());
            whilePatternParser.checkForSyntax();
            return whilePatternParser
                    .parse(tokens, parsedQuery, declarations, pos);
        }
    }
}

ParserResult PatternParser::parseValidSynonym(std::string synonymType,
    std::shared_ptr<Argument> arg,
    std::vector<Token> tokens,
    AbstractQuery &parsedQuery,
    std::unordered_map<std::string, std::shared_ptr<EntityArgument>> declarations,
    int pos) {
    try {
        ParserResult pr = getParser(synonymType, arg)->parse(
                tokens, parsedQuery, declarations, pos);
        return pr;
    } catch (ParserError pe) {
        ParserResult pr = checkForSyntaxError(tokens, parsedQuery, declarations, pos);
        updateIfSemantic(ErrorStatus::SEMANTIC, parsedQuery);
        return pr;
    }
}

ParserResult PatternParser::parse(std::vector<Token> tokens, AbstractQuery& parsedQuery,
    std::unordered_map<std::string, std::shared_ptr<EntityArgument>> declarations, int pos) {
    int clauses = 0;
    pos++;  // consume "pattern"
    // get pattern type
    while (pos < tokens.size() && (clauses == 0 || isAnd(tokens[pos]))) {
        pos = clauses == 0 ? pos : pos + consumeAnd(tokens[pos]);
        if (pos >= tokens.size()) {
            throw ParserError(ErrorStatus::SYNTAX);
        }
        ArgumentResult patternTypeResult = PatternTypeParser().parse(tokens, declarations, pos);
        pos = patternTypeResult.getPos();  // consume pattern type name
        updateIfSemantic(patternTypeResult.getErrorStatus(), parsedQuery);
        std::shared_ptr<Argument> patternType = patternTypeResult.getArg();
        std::string synonymType = dynamic_cast<EntityArgument*>(
            patternType.get())->getType();
        std::shared_ptr<Argument> arg = patternTypeResult.getArg();
        if (synonymType != DummyArgument::DUMMY) {
            ParserResult pr =
                    parseValidSynonym(synonymType, arg, tokens, parsedQuery, declarations, pos);
            pos = pr.getPos();
            declarations = pr.getDeclarations();
        } else {
            ParserResult pr = checkForSyntaxError(tokens, parsedQuery, declarations, pos);
            pos = pr.getPos();
            declarations = pr.getDeclarations();
        }
        clauses++;
    }
    if (clauses == 0) {
        throw ParserError(ErrorStatus::SYNTAX);
    }
    return {declarations, pos};
}
