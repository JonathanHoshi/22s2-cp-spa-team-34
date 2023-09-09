// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include <iostream>
#include <fstream>
#include "WhileNodeParser.h"

WhileNodeParser::WhileNodeParser(std::string path) {
    filePath = path;
    count = 1;
}

void WhileNodeParser::addStmtLstNodeParser(std::shared_ptr<StmtLstNodeParser> parser) {
    stmtLstNodeParser = parser;
}

void WhileNodeParser::addOperatorNodeParser(std::shared_ptr<OperatorNodeParser> parser) {
    operatorNodeParser = parser;
}

std::string WhileNodeParser::parse(WhileNode* node) {
    std::string curr = "whileNode" + std::to_string(count);
    count++;
    std::string stmtNo = std::to_string(node->getStmtNumber());
    std::string stmtLst = stmtLstNodeParser->parse(node->getStmtLst());
    std::string condExpr = operatorNodeParser->checkType(node->getCondition());
    std::ofstream outputFile;
    outputFile.open(filePath, std::ios::app);
    outputFile << "std::shared_ptr<WhileNode> " + curr
        + " = std::make_shared<WhileNode>(" + stmtNo + ");";
    outputFile << std::endl;
    outputFile << curr + "->setCondition(" + condExpr + ");";
    outputFile << std::endl;
    outputFile << curr + "->setStmtLst(" + stmtLst + ");";
    outputFile << std::endl;
    outputFile.close();

    return curr;
}
