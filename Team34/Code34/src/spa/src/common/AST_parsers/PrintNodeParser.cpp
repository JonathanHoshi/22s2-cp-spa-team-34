// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include <iostream>
#include <fstream>
#include "PrintNodeParser.h"

PrintNodeParser::PrintNodeParser(std::string path) {
    filePath = path;
    count = 1;
}

void PrintNodeParser::addVariableNodeParser(std::shared_ptr<VariableNodeParser> parser) {
    variableNodeParser = parser;
}

std::string PrintNodeParser::parse(PrintNode* node) {
    std::string curr = "printNode" + std::to_string(count);
    count++;
    std::string stmtNo = std::to_string(node->getStmtNumber());
    std::string var = variableNodeParser->parse(node->getVariable());
    std::ofstream outputFile;
    outputFile.open(filePath, std::ios::app);
    outputFile << "std::shared_ptr<PrintNode> " + curr
        + " = std::make_shared<PrintNode>(" + stmtNo + ");";
    outputFile << std::endl;
    outputFile << curr + "->setVariable(" + var + ");";
    outputFile << std::endl;
    outputFile.close();

    return curr;
}
