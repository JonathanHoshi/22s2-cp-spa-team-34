// Copyright (c) 2023 22s2-cp-spa-Team34. All rights reserved.

#pragma once
#include <exception>
#include <string>

class TransverseError : public std::exception {
    using std::exception::exception;
public:
    explicit TransverseError(std::string s);

private:
    std::string s;
};
