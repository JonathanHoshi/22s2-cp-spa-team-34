// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.
#include <string>
#include <utility>
#include "ReadParser.h"
#include "sp/node/VariableNode.h"
#include "sp/node/ReadNode.h"

ReadParser::ReadParser(std::vector<Token> tokens)
    : SPStmtParser(tokens) {}

std::shared_ptr<StmtNode> ReadParser::parse() {
    std::string variable;
    std::shared_ptr<ReadNode> readNode;
    std::shared_ptr<VariableNode> variableNode;

    verifyTokenAndTraverse("IDENTITY", "read");
    variable = verifyTokenAndGetValue("IDENTITY");
    traverse();
    verifyTokenAndTraverse("PUNCTUATION", ";");
    variableNode = std::make_shared<VariableNode>(variable);
    readNode = std::make_shared<ReadNode>(getStmtNo());
    readNode->setVariable(move(variableNode));

    return readNode;
}
