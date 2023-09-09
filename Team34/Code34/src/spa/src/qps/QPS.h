// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once

#include <list>
#include <string>

#include "common/tokenizer/Tokenizer.h"
#include "pkb/interfaces/IAffectsClearer.h"
#include "pkb/interfaces/INextTClearer.h"
#include "qps/preprocessor/parser/ParserManager.h"
#include "qps/query/AbstractQuery.h"
#include "qps/evaluator/Evaluator.h"
#include "qps/formatter/Formatter.h"
#include "../common/exceptions/ParserError.h"

class QPS {
public:
    std::list<std::string> process(std::string query, DI& di);
};
