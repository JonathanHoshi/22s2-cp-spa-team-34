// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#include "Argument.h"

Argument::Argument(std::string value) {
    this->value = value;
}

std::string Argument::getValue() {
    return this->value;
}

bool Argument::operator==(const Argument& other) const {
    return typeid(*this) == typeid(other) && this->value == other.value;
}
