// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include <iostream>
#include <fstream>
#include "CallNodeParser.h"

CallNodeParser::CallNodeParser(std::string path) {
    filePath = path;
    count = 1;
}

std::string CallNodeParser::parse(CallNode* node) {
    std::string curr = "callNode" + std::to_string(count);
    count++;
    std::string stmtNo = std::to_string(node->getStmtNumber());
    std::string procedureCall = node->getProcedureName();
    std::ofstream outputFile;
    outputFile.open(filePath, std::ios::app);
    outputFile << "std::shared_ptr<CallNode> " + curr
        + " = std::make_shared<CallNode>(" + stmtNo + ", \"" + procedureCall + "\");";
    outputFile << std::endl;
    outputFile.close();

    return curr;
}
