// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include <iostream>
#include <fstream>
#include "ProcedureNodeParser.h"

ProcedureNodeParser::ProcedureNodeParser(std::string path) {
    filePath = path;
    count = 1;
}

void ProcedureNodeParser::addStmtLstNodeParser(std::shared_ptr<StmtLstNodeParser> parser) {
    stmtLstNodeParser = parser;
}

std::string ProcedureNodeParser::parse(ProcedureNode* node) {
    std::string curr = "procedureNode" + std::to_string(count);
    count++;
    std::string name = node->getProcedureName();
    std::string stmtLst = stmtLstNodeParser->parse(node->getStmtList());
    std::ofstream outputFile;
    outputFile.open(filePath, std::ios::app);
    outputFile << "std::shared_ptr<ProcedureNode> " + curr
        + " = std::make_shared<ProcedureNode>(\"" + name + "\");";
    outputFile << std::endl;
    outputFile << curr + "->setStmtList(" + stmtLst + ");";
    outputFile << std::endl;
    outputFile.close();

    return curr;
}
