// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "NameValidator.h"

bool NameValidator::validate(std::string val) {
    return std::all_of(val.begin(), val.end(), [](char const& c) {
        return std::isalnum(c);
        });
}
