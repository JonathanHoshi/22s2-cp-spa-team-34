// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "ParserError.h"

ParserError::ParserError(ErrorStatus e) : e(e), std::exception() {}

ErrorStatus ParserError::status() {
    return e;
}
