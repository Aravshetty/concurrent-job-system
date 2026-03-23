#include <iostream>

#include "include/threadpool/ThreadPool.hpp"
#include "include/jobs/SumJob.hpp"
#include "include/jobs/PrimeJob.hpp"
#include "include/jobs/SleepJob.hpp"
#include "include/jobs/FailingJob.hpp"

int main() {

    ThreadPool pool(3);

    auto f1 = pool.submit(std::make_unique<SumJob>(1, 100));
    auto f2 = pool.submit(std::make_unique<PrimeJob>(1, 100));
    auto f3 = pool.submit(std::make_unique<SleepJob>(2));
    auto f4 = pool.submit(std::make_unique<FailingJob>());

    std::cout << "Jobs submitted...\n";

    try {
        auto r1 = f1.get();
        std::cout << r1.message << " -> " << r1.value << "\n";
    } catch (...) {
        std::cout << "Job 1 failed\n";
    }

    try {
        auto r2 = f2.get();
        std::cout << r2.message << " -> " << r2.value << "\n";
    } catch (...) {
        std::cout << "Job 2 failed\n";
    }

    try {
        auto r3 = f3.get();
        std::cout << r3.message << " -> " << r3.value << "\n";
    } catch (...) {
        std::cout << "Job 3 failed\n";
    }

    try {
        auto r4 = f4.get();
        std::cout << r4.message << " -> " << r4.value << "\n";
    } catch (...) {
        std::cout << "Job 4 failed (expected)\n";
    }

    std::cout << "\n=== Metrics ===\n";
    std::cout << "Submitted: " << pool.metrics.tasksSubmitted << "\n";
    std::cout << "Completed: " << pool.metrics.tasksCompleted << "\n";
    std::cout << "Failed: " << pool.metrics.tasksFailed << "\n";

    return 0;
}