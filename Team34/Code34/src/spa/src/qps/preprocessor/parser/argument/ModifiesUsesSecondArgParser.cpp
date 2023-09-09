// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "ModifiesUsesSecondArgParser.h"

ModifiesUsesSecondArgParser::ModifiesUsesSecondArgParser() : ArgumentParser() {}

ArgumentResult ModifiesUsesSecondArgParser::parse(std::vector<Token> tokens,
    std::unordered_map<std::string, std::shared_ptr<EntityArgument>> declarations,
    int pos) {
    EntRefParser entRefParser = EntRefParser();
    ArgumentResult argumentResult = entRefParser.parse(tokens, declarations, pos);
    std::shared_ptr<Argument> secondArg = argumentResult.getArg();
    pos = argumentResult.getPos();
    errorStatus = argumentResult.getErrorStatus();
    if (!ModifiesUsesSecondArg::checkInstance(secondArg.get())) {
        errorStatus = ErrorStatus::SEMANTIC;
        secondArg = std::make_shared<DummyArgument>();
    }
    return {secondArg, pos, errorStatus};
}
