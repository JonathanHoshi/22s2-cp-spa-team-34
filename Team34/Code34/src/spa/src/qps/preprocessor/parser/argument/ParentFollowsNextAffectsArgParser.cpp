// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "ParentFollowsNextAffectsArgParser.h"

ParentFollowsNextAffectsArgParser::ParentFollowsNextAffectsArgParser() : ArgumentParser() {}

ArgumentResult ParentFollowsNextAffectsArgParser::parse(std::vector<Token> tokens,
    std::unordered_map<std::string, std::shared_ptr<EntityArgument>> declarations, int pos) {
    StmtRefParser stmtRefParser = StmtRefParser();
    ArgumentResult argumentResult = stmtRefParser.parse(tokens, declarations, pos);
    std::shared_ptr<Argument> arg = argumentResult.getArg();
    pos = argumentResult.getPos();
    errorStatus = argumentResult.getErrorStatus();
    if (!ParentFollowsNextArg::checkInstance(arg.get())) {
        errorStatus = ErrorStatus::SEMANTIC;
        arg = std::make_shared<DummyArgument>();
    }
    return {arg, pos, errorStatus};
}
