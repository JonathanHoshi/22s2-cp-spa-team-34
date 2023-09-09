// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include <utility>
#include "StmtLstParser.h"

StmtLstParser::StmtLstParser(std::vector<Token> tokens)
    : SPParser(tokens) {}

void StmtLstParser::addStmtParser(std::shared_ptr<SPStmtParser> parser) {
    stmtParsers.push_back(parser);
}

std::shared_ptr<StmtNode> StmtLstParser::consumeStmt() {
    std::shared_ptr<StmtNode> stmtNode = nullptr;

    for (std::shared_ptr<SPStmtParser> stmtParser : stmtParsers) {
        try {
            stmtParser->setStmtNo(getStmtNo());
            stmtParser->setPos(getPos());
            stmtNode = stmtParser->parse();
            setPos(stmtParser->getPos());
            break;
        } catch (ParserError e) {
            // iterating through to find the correct stmtParser
        }
    }

    if (stmtNode == nullptr) {
        throw ParserError(ErrorStatus::SYNTAX);
    }

    return stmtNode;
}

std::shared_ptr<StmtLstNode> StmtLstParser::parse() {
    std::shared_ptr<StmtNode> stmtNode;
    std::shared_ptr<StmtLstNode> stmtLstNode = std::make_shared<StmtLstNode>();

    while (!checkToken("PUNCTUATION", "}")) {
        stmtNo++;
        stmtNode = consumeStmt();
        stmtLstNode->addStmt(move(stmtNode));
    }

    if (stmtLstNode->getStmtCount() == 0) {
        throw ParserError(ErrorStatus::SYNTAX);
    }

    return stmtLstNode;
}
