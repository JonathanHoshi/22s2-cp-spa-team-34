// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once
#include <exception>
#include <string>
#include "ErrorStatus.h"

class ParserError : public std::exception {
private:
    ErrorStatus e;
public:
    explicit ParserError(ErrorStatus e);
    ErrorStatus status();
};
