// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.
#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
#include "di/IService.h"

class IAffectsGetter : public virtual IService {
public:
    ~IAffectsGetter() override = default;

    virtual bool isAffects(const int& keyStmt, const int& affectedStmt) = 0;
    virtual bool isAffectsT(const int& keyStmt, const int& affectedStmt) = 0;

    virtual bool hasAffects() = 0;
    virtual bool hasAffectsByKeyStmt(const int& keyStmt) = 0;
    virtual bool hasAffectsByAffectedStmt(const int& affectedStmt) = 0;

    virtual std::unordered_map<int, std::unordered_set<int>> getAffectsEntries() = 0;
    virtual std::unordered_map<int, std::unordered_set<int>> getAffectsTEntries() = 0;

    virtual std::unordered_set<int> getKeyStmtsByAffectedStmt(const int& affectedStmt) = 0;
    virtual std::unordered_set<int> getAffectedStmtsByKeyStmt(const int& keyStmt) = 0;
    virtual std::unordered_set<int> getTKeyStmtsByAffectedStmt(const int& affectedStmt) = 0;
    virtual std::unordered_set<int> getTAffectedStmtsByKeyStmt(const int& keyStmt) = 0;
};
