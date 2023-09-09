// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "CallsArgParser.h"

CallsArgParser::CallsArgParser() : ArgumentParser() {}

ArgumentResult CallsArgParser::parse(std::vector<Token> tokens,
    std::unordered_map<std::string, std::shared_ptr<EntityArgument>> declarations, int pos) {
    EntRefParser entRefParser = EntRefParser();
    ArgumentResult argumentResult = entRefParser.parse(tokens, declarations, pos);
    std::shared_ptr<Argument> arg = argumentResult.getArg();
    pos = argumentResult.getPos();
    errorStatus = argumentResult.getErrorStatus();
    if (!CallsArg::checkInstance(arg.get())) {
        errorStatus = ErrorStatus::SEMANTIC;
        arg = std::make_shared<DummyArgument>();
    }
    return {arg, pos, errorStatus};
}
