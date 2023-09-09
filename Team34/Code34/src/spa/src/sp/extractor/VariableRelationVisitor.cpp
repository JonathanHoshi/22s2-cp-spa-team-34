// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "VariableRelationVisitor.h"
#include "common/CollectionUtils.h"
#include "sp/node/StmtLstNode.h"
#include "sp/node/CallNode.h"

VariableRelationVisitor::VariableRelationVisitor() {}

void VariableRelationVisitor::mergeStmtList(std::unordered_set<std::string>& copyTo,
    StmtLstNode& stmtList) {
    for (int i = 0; i < stmtList.getStmtCount(); i++) {
        StmtNode* child = stmtList.getStmt(i);
        auto iter = statementMap.find(child->getStmtNumber());
        if (iter != statementMap.end())
            CollectionUtils::merge(copyTo, iter->second);
    }
}

void VariableRelationVisitor::extract(CallNode& node) {
    std::unordered_set<std::string> variableLst = procedureMap.at(node.getProcedureName());
    CollectionUtils::insert(statementMap, node.getStmtNumber(), variableLst);
}
