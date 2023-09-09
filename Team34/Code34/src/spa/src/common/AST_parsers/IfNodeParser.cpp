// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include <iostream>
#include <fstream>
#include "IfNodeParser.h"

IfNodeParser::IfNodeParser(std::string path) {
    filePath = path;
    count = 1;
}

void IfNodeParser::addStmtLstNodeParser(std::shared_ptr<StmtLstNodeParser> parser) {
    stmtLstNodeParser = parser;
}

void IfNodeParser::addOperatorNodeParser(std::shared_ptr<OperatorNodeParser> parser) {
    operatorNodeParser = parser;
}

std::string IfNodeParser::parse(IfNode* node) {
    std::string curr = "ifNode" + std::to_string(count);
    count++;
    std::string stmtNo = std::to_string(node->getStmtNumber());
    std::string thenStmtLst = stmtLstNodeParser->parse(node->getThen());
    std::string elseStmtLst = stmtLstNodeParser->parse(node->getElse());
    std::string condExpr = operatorNodeParser->checkType(node->getCondition());
    std::ofstream outputFile;
    outputFile.open(filePath, std::ios::app);
    outputFile << "std::shared_ptr<IfNode> " + curr
        + " = std::make_shared<IfNode>(" + stmtNo + ");";
    outputFile << std::endl;
    outputFile << curr + "->setCondition(" + condExpr + ");";
    outputFile << std::endl;
    outputFile << curr + "->setThen(" + thenStmtLst + ");";
    outputFile << std::endl;
    outputFile << curr + "->setElse(" + elseStmtLst + ");";
    outputFile << std::endl;
    outputFile.close();

    return curr;
}
