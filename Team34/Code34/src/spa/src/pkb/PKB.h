// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once

#include "di/DI.h"

#include "pkb/tables/ConstTable.h"
#include "pkb/tables/ProcTable.h"
#include "pkb/tables/VarTable.h"
#include "pkb/tables/StmtTable.h"
#include "pkb/tables/CallsTable.h"
#include "pkb/tables/FollowsTable.h"
#include "pkb/tables/ModifiesTable.h"
#include "pkb/tables/ParentTable.h"
#include "pkb/tables/UsesTable.h"
#include "pkb/tables/AssignPatternTable.h"
#include "pkb/tables/IfPatternTable.h"
#include "pkb/tables/WhilePatternTable.h"
#include "pkb/tables/NextTable.h"
#include "pkb/tables/AffectsTable.h"

class PKB {
public:
    explicit PKB(DI& di);
};
