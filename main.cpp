#include <iostream>
#include <memory>
#include <vector>

#include "include/jobs/SumJob.hpp"
#include "include/jobs/PrimeJob.hpp"
#include "include/jobs/SleepJob.hpp"
#include "include/jobs/FailingJob.hpp"
#include "include/queue/JobQueue.hpp"
int main() {

    JobQueue queue;

    queue.push(std::make_unique<SumJob>(1, 100));
    queue.push(std::make_unique<PrimeJob>(1, 100));

    while (true) {
        auto job = queue.tryPop();

        if (!job) break;

        try {
            JobResult result = job->run();
            std::cout << result.message << " -> " << result.value << "\n";
        } catch (...) {
            std::cout << "Job failed\n";
        }
    }

    return 0;
}