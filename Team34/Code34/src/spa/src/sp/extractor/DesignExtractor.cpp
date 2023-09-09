// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>

#include "DesignExtractor.h"
#include "EntityExtractorVisitor.h"
#include "ModifyRelationVisitor.h"
#include "ParentRelationVisitor.h"
#include "FollowRelationVisitor.h"
#include "UsesRelationVisitor.h"
#include "PatternExtractorVisitor.h"
#include "CallsExtractorVisitor.h"
#include "CFGExtractorVisitor.h"
#include "TopologicalSortVisitor.h"

#include "pkb/interfaces/ICallsAdder.h"
#include "pkb/interfaces/IAssignPatternAdder.h"
#include "pkb/interfaces/IWhilePatternAdder.h"
#include "pkb/interfaces/IIfPatternAdder.h"
#include "pkb/interfaces/IUsesAdder.h"
#include "pkb/interfaces/IModifiesAdder.h"
#include "pkb/interfaces/IParentAdder.h"
#include "pkb/interfaces/IFollowsAdder.h"
#include "pkb/interfaces/INextAdder.h"

DesignExtractor::DesignExtractor() {}


void DesignExtractor::registerExtractors(DI& di) {
    extractors.push_back(new EntityExtractorVisitor(di.getService<IStmtAdder>(),
        di.getService<IProcAdder>(),
        di.getService<IConstAdder>(), di.getService<IVarAdder>()));

    extractors.push_back(new ModifyRelationVisitor(di.getService<IModifiesAdder>()));

    extractors.push_back(new ParentRelationVisitor(di.getService<IParentAdder>()));

    extractors.push_back(new FollowRelationVisitor(di.getService<IFollowsAdder>()));

    extractors.push_back(new UsesRelationVisitor(di.getService<IUsesAdder>()));

    extractors.push_back(new PatternExtractorVisitor(di.getService<IAssignPatternAdder>(),
        di.getService<IIfPatternAdder>(), di.getService<IWhilePatternAdder>()));

    extractors.push_back(new CallsExtractorVisitor(di.getService<ICallsAdder>()));

    extractors.push_back(new CFGExtractorVisitor(di.getService<INextAdder>()));
}

void DesignExtractor::clearExtractors() {
    for (int i = 0; i < extractors.size(); i++) {
        delete(extractors.at(i));
    }
    extractors.clear();
}

void DesignExtractor::extract(RootNode& root, DI& di) {
    TopologicalSortVisitor sorter;
    sorter.begin(root);  // this should be in parser

    registerExtractors(di);
    for (int i = 0; i < extractors.size(); i++) {
        extractors.at(i)->begin(root);
        extractors.at(i)->transfer();
    }
    clearExtractors();
}
