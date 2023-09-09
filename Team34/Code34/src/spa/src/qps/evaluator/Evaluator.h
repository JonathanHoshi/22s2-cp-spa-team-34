// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once

#include <memory>
#include <vector>

#include "qps/query/QueryProcessor.h"
#include "di/DI.h"
#include "qps/argument/Argument.h"
#include "qps/argument/entity/EntityArgument.h"
#include "qps/clause/Clause.h"
#include "qps/query/AbstractQuery.h"

class Evaluator {
private:
    DI* diInterface;
    QueryProcessor processor;

    void handleQueryProcess(AbstractQuery& query);

public:
    Evaluator();
    explicit Evaluator(DI* diInterface);

    void processQuery(AbstractQuery& query);
};
