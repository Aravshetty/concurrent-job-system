#pragma once
#include "../core/Job.hpp"

class SumJob : public Job {
private:
    int l, r;

public:
    SumJob(int l, int r) : l(l), r(r) {}

    JobResult run() override {
        int sum = 0;
        for (int i = l; i <= r; i++) {
            sum += i;
        }

        return {true, "Sum computed", sum};
    }

    int priority() const override {
        return 1;
    }
};