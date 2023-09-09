// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.
#include <vector>
#include "QPS.h"

std::list<std::string> QPS::process(std::string query, DI& di) {
    Tokenizer tokenizer = Tokenizer();
    std::vector<Token> tokens = tokenizer.tokenize(query);
    AbstractQuery absQuery;
    ParserManager parser;
    if (tokenizer.hasError()) {
        absQuery.updateStatus(ErrorStatus::SYNTAX);
    } else {
        try {
            parser.parse(tokens, absQuery);
        } catch (ParserError pe) {
            absQuery.updateStatus(pe.status());
        }
    }
    Evaluator evaluator(&di);
    evaluator.processQuery(absQuery);
    Formatter formatter;

    std::list<std::string> result = formatter.formatResult(absQuery);
    di.getService<IAffectsClearer>().clearAffectsAndT();
    di.getService<INextTClearer>().clearNextT();
    return result;
}
