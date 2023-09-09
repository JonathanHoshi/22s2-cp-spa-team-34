// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "StmtRefParser.h"

StmtRefParser::StmtRefParser(): ArgumentParser() {}

ArgumentResult StmtRefParser::parse(std::vector<Token> tokens,
                                    std::unordered_map<std::string,
                                    std::shared_ptr<EntityArgument>> declarations,
                                    int pos) {
    Token stmtToken = tokens[pos];
    pos++;
    std::shared_ptr<Argument> arg;
    if (stmtToken.getType() == NumberToken::TYPE_NAME) {
        arg = std::make_shared<IntInput>(stmtToken.getValue());
    } else if (isWildcard(stmtToken)) {
        arg = std::make_shared<WildcardEntity>();
    } else if (stmtToken.getType() == IdentityToken::TYPE_NAME) {
        ArgumentResult ar = ElementParser(false).parse(tokens, declarations, pos - 1);
        arg = ar.getArg();
        pos = ar.getPos();
        errorStatus = ar.getErrorStatus();
    } else {
        throw ParserError(ErrorStatus::SYNTAX);
    }
    return {arg, pos, errorStatus};
}
