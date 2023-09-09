// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.
#include <string>
#include <utility>
#include "PrintParser.h"
#include "sp/node/VariableNode.h"
#include "sp/node/PrintNode.h"

PrintParser::PrintParser(std::vector<Token> tokens)
    : SPStmtParser(tokens) {}

std::shared_ptr<StmtNode> PrintParser::parse() {
    std::string variable;
    std::shared_ptr<PrintNode> printNode;
    std::shared_ptr<VariableNode> variableNode;

    verifyTokenAndTraverse("IDENTITY", "print");
    variable = verifyTokenAndGetValue("IDENTITY");
    traverse();
    verifyTokenAndTraverse("PUNCTUATION", ";");
    variableNode = std::make_shared<VariableNode>(variable);
    printNode = std::make_shared<PrintNode>(getStmtNo());
    printNode->setVariable(move(variableNode));

    return printNode;
}
