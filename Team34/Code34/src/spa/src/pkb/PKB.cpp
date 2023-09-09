// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include <memory>
#include "pkb/PKB.h"

PKB::PKB(DI& di) {
    auto constTable = std::make_shared<ConstTable>();
    di.registerService<IConstAdder>(constTable);
    di.registerService<IConstGetter>(constTable);

    auto procTable = std::make_shared<ProcTable>();
    di.registerService<IProcAdder>(procTable);
    di.registerService<IProcGetter>(procTable);

    auto varTable = std::make_shared<VarTable>();
    di.registerService<IVarAdder>(varTable);
    di.registerService<IVarGetter>(varTable);

    auto stmtTable = std::make_shared<StmtTable>();
    di.registerService<IStmtAdder>(stmtTable);
    di.registerService<IStmtGetter>(stmtTable);

    auto callsTable = std::make_shared<CallsTable>();
    di.registerService<ICallsAdder>(callsTable);
    di.registerService<ICallsGetter>(callsTable);

    auto followsTable = std::make_shared<FollowsTable>();
    di.registerService<IFollowsAdder>(followsTable);
    di.registerService<IFollowsGetter>(followsTable);

    auto modifiesTable = std::make_shared<ModifiesTable>();
    di.registerService<IModifiesAdder>(modifiesTable);
    di.registerService<IModifiesGetter>(modifiesTable);

    auto parentTable = std::make_shared<ParentTable>();
    di.registerService<IParentAdder>(parentTable);
    di.registerService<IParentGetter>(parentTable);

    auto usesTable = std::make_shared<UsesTable>();
    di.registerService<IUsesAdder>(usesTable);
    di.registerService<IUsesGetter>(usesTable);

    auto assignPatternTable = std::make_shared<AssignPatternTable>();
    di.registerService<IAssignPatternAdder>(assignPatternTable);
    di.registerService<IAssignPatternGetter>(assignPatternTable);

    auto ifPatternTable = std::make_shared<IfPatternTable>();
    di.registerService<IIfPatternAdder>(ifPatternTable);
    di.registerService<IIfPatternGetter>(ifPatternTable);

    auto whilePatternTable = std::make_shared<WhilePatternTable>();
    di.registerService<IWhilePatternAdder>(whilePatternTable);
    di.registerService<IWhilePatternGetter>(whilePatternTable);

    auto nextTable = std::make_shared<NextTable>();
    di.registerService<INextAdder>(nextTable);
    di.registerService<INextGetter>(nextTable);
    di.registerService<INextTClearer>(nextTable);

    auto affectsTable = std::make_shared<AffectsTable>(*modifiesTable,
        *usesTable, *nextTable, *parentTable, *stmtTable);
    di.registerService<IAffectsClearer>(affectsTable);
    di.registerService<IAffectsGetter>(affectsTable);
}
