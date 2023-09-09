// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include <iostream>
#include <fstream>
#include "ReadNodeParser.h"

ReadNodeParser::ReadNodeParser(std::string path) {
    filePath = path;
    count = 1;
}

void ReadNodeParser::addVariableNodeParser(std::shared_ptr<VariableNodeParser> parser) {
    variableNodeParser = parser;
}

std::string ReadNodeParser::parse(ReadNode* node) {
    std::string curr = "readNode" + std::to_string(count);
    count++;
    std::string stmtNo = std::to_string(node->getStmtNumber());
    std::string var = variableNodeParser->parse(node->getVariable());
    std::ofstream outputFile;
    outputFile.open(filePath, std::ios::app);
    outputFile << "std::shared_ptr<ReadNode> " + curr
        + " = std::make_shared<ReadNode>(" + stmtNo + ");";
    outputFile << std::endl;
    outputFile << curr + "->setVariable(" + var + ");";
    outputFile << std::endl;
    outputFile.close();

    return curr;
}
