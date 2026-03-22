#pragma once
#include "../core/Job.hpp"
#include <stdexcept>

class FailingJob : public Job {
public:
    JobResult run() override {
        throw std::runtime_error("Job failed intentionally");
    }

    int priority() const override {
        return 3;
    }
};