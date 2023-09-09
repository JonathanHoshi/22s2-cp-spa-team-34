// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include <utility>
#include <string>
#include "CallParser.h"
#include "sp/node/CallNode.h"

CallParser::CallParser(std::vector<Token> tokens)
    : SPStmtParser(tokens) {}

std::shared_ptr<StmtNode> CallParser::parse() {
    std::string procedureName;
    std::shared_ptr<StmtNode> callNode;

    verifyTokenAndTraverse("IDENTITY", "call");
    procedureName = verifyTokenAndGetValue("IDENTITY");
    traverse();
    verifyTokenAndTraverse("PUNCTUATION", ";");
    callNode = std::make_shared<CallNode>(getStmtNo(), procedureName);

    return callNode;
}
