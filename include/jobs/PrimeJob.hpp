#pragma once
#include "../core/Job.hpp"

class PrimeJob : public Job {
private:
    int l, r;

    bool isPrime(int x) {
        if (x < 2) return false;
        for (int i = 2; i * i <= x; i++) {
            if (x % i == 0) return false;
        }
        return true;
    }

public:
    PrimeJob(int l, int r) : l(l), r(r) {}

    JobResult run() override {
        int count = 0;
        for (int i = l; i <= r; i++) {
            if (isPrime(i)) count++;
        }

        return {true, "Prime count computed", count};
    }

    int priority() const override {
        return 2;
    }
};