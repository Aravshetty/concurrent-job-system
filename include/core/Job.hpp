#pragma once
#include "JobResult.hpp"

class Job {
public:
    virtual ~Job() = default;

    virtual JobResult run() = 0;

    virtual int priority() const {
        return 0;
    }
};