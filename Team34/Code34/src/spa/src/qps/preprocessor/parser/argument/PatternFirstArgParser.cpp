// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "PatternFirstArgParser.h"

PatternFirstArgParser::PatternFirstArgParser() : ArgumentParser() {}

ArgumentResult PatternFirstArgParser::parse(std::vector<Token> tokens,
    std::unordered_map<std::string, std::shared_ptr<EntityArgument>> declarations,
    int pos) {
    EntRefParser entRefParser = EntRefParser();
    ArgumentResult argumentResult = entRefParser.parse(tokens, declarations, pos);
    std::shared_ptr<Argument> argument = argumentResult.getArg();
    pos = argumentResult.getPos();
    errorStatus = argumentResult.getErrorStatus();
    if (!PatternFirstArg::checkInstance(argument.get())) {
        errorStatus = ErrorStatus::SEMANTIC;
        argument = std::make_shared<DummyArgument>();
    }
    return {argument, pos, errorStatus};
}
