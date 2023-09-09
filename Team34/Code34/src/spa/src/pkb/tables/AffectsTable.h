// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once

#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include "pkb/base/BaseMapSet.h"
#include "CyclicTTable.h"
#include "pkb/interfaces/IAffectsGetter.h"
#include "pkb/interfaces/IAffectsClearer.h"
#include "pkb/interfaces/IModifiesGetter.h"
#include "pkb/interfaces/IUsesGetter.h"
#include "pkb/interfaces/INextGetter.h"
#include "pkb/interfaces/IParentGetter.h"
#include "pkb/interfaces/IStmtGetter.h"

class AffectsTable : public CyclicTTable, public IAffectsGetter, public IAffectsClearer {
private:
    BaseMapSet<int, int> keyToValEntries;    // Store key -> val pairs of Next
    BaseMapSet<int, int> valToKeyEntries;    // Store val -> key pairs of Next
    BaseMapSet<int, int> keyToValTEntries;    // Store key -> val pairs of Next
    BaseMapSet<int, int> valToKeyTEntries;    // Store val -> key pairs of Next

    std::unordered_set<int> computedAffects;
    std::unordered_set<int> computedAffected;
    bool computedAffectsT = false;

    IModifiesGetter* modifiesGetter;
    IUsesGetter* usesGetter;
    INextGetter* nextGetter;
    IParentGetter* parentGetter;
    IStmtGetter* stmtGetter;

    void generateAffects(const int& key);
    void generateAffected(const int& value);
    bool handleAffects(const int& key, const int& value, const std::string& var);

public:
    AffectsTable(IModifiesGetter& modifiesGetter, IUsesGetter& usesGetter,
        INextGetter& nextGetter, IParentGetter& parentGetter, IStmtGetter& stmtGetter);

    // Inherited via IAffectsGetter
    bool isAffects(const int& keyStmt, const int& affectedStmt) override;
    bool isAffectsT(const int& keyStmt, const int& affectedStmt) override;
    bool hasAffects() override;
    bool hasAffectsByKeyStmt(const int& keyStmt) override;
    bool hasAffectsByAffectedStmt(const int& affectedStmt) override;
    std::unordered_map<int, std::unordered_set<int>> getAffectsEntries() override;
    std::unordered_map<int, std::unordered_set<int>> getAffectsTEntries() override;
    std::unordered_set<int> getKeyStmtsByAffectedStmt(const int& affectedStmt) override;
    std::unordered_set<int> getAffectedStmtsByKeyStmt(const int& keyStmt) override;
    std::unordered_set<int> getTKeyStmtsByAffectedStmt(const int& affectedStmt) override;
    std::unordered_set<int> getTAffectedStmtsByKeyStmt(const int& keyStmt) override;

    // Inherited via IAffectsClearer
    void clearAffectsAndT() override;
};
