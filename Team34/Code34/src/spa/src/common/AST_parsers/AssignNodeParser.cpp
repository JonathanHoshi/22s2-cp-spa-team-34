// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include <iostream>
#include <fstream>
#include "AssignNodeParser.h"

AssignNodeParser::AssignNodeParser(std::string path) {
    filePath = path;
    count = 1;
}

void AssignNodeParser::addVariableNodeParser(std::shared_ptr<VariableNodeParser> parser) {
    variableNodeParser = parser;
}

void AssignNodeParser::addOperatorNodeParser(std::shared_ptr<OperatorNodeParser> parser) {
    operatorNodeParser = parser;
}

std::string AssignNodeParser::parse(AssignNode* node) {
    std::string curr = "assignNode" + std::to_string(count);
    count++;
    std::string stmtNo = std::to_string(node->getStmtNumber());
    std::string variable = variableNodeParser->parse(node->getVariable());
    std::string expr = operatorNodeParser->checkType(node->getExpression());
    std::ofstream outputFile;
    outputFile.open(filePath, std::ios::app);

    outputFile << "std::shared_ptr<AssignNode> " + curr
        + " = std::make_shared<AssignNode>(" + stmtNo + ");";
    outputFile << std::endl;
    outputFile << curr + "->setVariable(" + variable + ");";
    outputFile << std::endl;
    outputFile << curr + "->setExpression(" + expr + ");";
    outputFile.close();

    return curr;
}
