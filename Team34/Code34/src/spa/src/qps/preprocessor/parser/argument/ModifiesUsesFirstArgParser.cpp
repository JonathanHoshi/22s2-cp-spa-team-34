// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "ModifiesUsesFirstArgParser.h"

ModifiesUsesFirstArgParser::ModifiesUsesFirstArgParser() : ArgumentParser() {}

ArgumentResult ModifiesUsesFirstArgParser::parseStmt(std::vector<Token> tokens,
                                             std::unordered_map<std::string,
                                             std::shared_ptr<EntityArgument>> declarations,
                                             int pos) {
    StmtRefParser stmtRefParser = StmtRefParser();
    return stmtRefParser.parse(tokens, declarations, pos);
}

ArgumentResult ModifiesUsesFirstArgParser::parse(std::vector<Token> tokens,
    std::unordered_map<std::string, std::shared_ptr<EntityArgument>> declarations,
    int pos) {
    std::shared_ptr<ArgumentResult> argumentResult;
    std::shared_ptr<Argument> argument;
    try {
        StmtRefParser stmtRefParser = StmtRefParser();
        argumentResult = std::make_shared<ArgumentResult>(stmtRefParser
                .parse(tokens, declarations, pos));
        argument = argumentResult.get()->getArg();
        pos = argumentResult.get()->getPos();
        errorStatus = argumentResult.get()->getErrorStatus();
    } catch (ParserError pe) {
        EntRefParser entRefParser = EntRefParser();
        argumentResult = std::make_shared<ArgumentResult>(entRefParser
                .parse(tokens, declarations, pos));
        argument = argumentResult.get()->getArg();
        pos = argumentResult.get()->getPos();
        errorStatus = argumentResult.get()->getErrorStatus();
    }
    if (!ModifiesUsesFirstArg::checkInstance(argument.get())) {
        errorStatus = ErrorStatus::SEMANTIC;
        argument = std::make_shared<DummyArgument>();
    }
    return {argument, pos, errorStatus};
}
