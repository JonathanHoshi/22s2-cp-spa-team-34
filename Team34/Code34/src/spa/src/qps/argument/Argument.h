// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once

#include <string>
#include <memory>
#include <unordered_set>

class Argument {
protected:
    std::string value;
    explicit Argument(std::string value);

public:
    virtual std::string getValue();
    virtual bool operator==(const Argument& other) const;
};
