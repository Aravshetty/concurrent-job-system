#pragma once
#include <string>

struct JobResult {
    bool success;
    std::string message;
    int value;
};