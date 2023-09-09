// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include <iostream>
#include <fstream>
#include "StmtLstNodeParser.h"
#include "IfNodeParser.h"
#include "WhileNodeParser.h"

StmtLstNodeParser::StmtLstNodeParser(std::string path) {
    filePath = path;
    count = 1;
}

void StmtLstNodeParser::addAssignNodeParser(std::shared_ptr<AssignNodeParser> parser) {
    assignNodeParser = parser;
}

void StmtLstNodeParser::addCallNodeParser(std::shared_ptr<CallNodeParser> parser) {
    callNodeParser = parser;
}

void StmtLstNodeParser::addPrintNodeParser(std::shared_ptr<PrintNodeParser> parser) {
    printNodeParser = parser;
}

void StmtLstNodeParser::addIfNodeParser(std::shared_ptr<IfNodeParser> parser) {
    ifNodeParser = parser;
}

void StmtLstNodeParser::addWhileNodeParser(std::shared_ptr<WhileNodeParser> parser) {
    whileNodeParser = parser;
}

void StmtLstNodeParser::addReadNodeParser(std::shared_ptr<ReadNodeParser> parser) {
    readNodeParser = parser;
}

std::string StmtLstNodeParser::checkType(EntityNode* node) {
    std::string output = "";

    if (dynamic_cast<AssignNode*>(node) != nullptr) {
        output = assignNodeParser->parse(dynamic_cast<AssignNode*>(node));
    } else if (dynamic_cast<CallNode*>(node) != nullptr) {
        output = callNodeParser->parse(dynamic_cast<CallNode*>(node));
    } else if (dynamic_cast<ReadNode*>(node) != nullptr) {
        output = readNodeParser->parse(dynamic_cast<ReadNode*>(node));
    } else if (dynamic_cast<PrintNode*>(node) != nullptr) {
        output = printNodeParser->parse(dynamic_cast<PrintNode*>(node));
    } else if (dynamic_cast<IfNode*>(node) != nullptr) {
        output = ifNodeParser->parse(dynamic_cast<IfNode*>(node));
    } else if (dynamic_cast<WhileNode*>(node) != nullptr) {
        output = whileNodeParser->parse(dynamic_cast<WhileNode*>(node));
    } else {}

    return output;
}

std::string StmtLstNodeParser::parse(StmtLstNode* node) {
    std::string curr = "stmtLstNode" + std::to_string(count);
    count++;

    std::ofstream outputFile;
    outputFile.open(filePath, std::ios::app);
    outputFile << "std::shared_ptr<StmtLstNode> " + curr
        + " = std::make_shared<StmtLstNode>();";
    outputFile << std::endl;
    outputFile.close();

    for (int i = 0; i < node->getStmtCount(); i++) {
        std::string stmt = checkType(node->getStmt(i));
        outputFile.open(filePath, std::ios::app);
        outputFile << curr + "->addStmt(" + stmt + ");";
        outputFile << std::endl;
        outputFile.close();
    }

    return curr;
}
