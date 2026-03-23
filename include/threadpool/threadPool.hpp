#pragma once
#include <vector>
#include <thread>
#include <future>

#include "../queue/BlockingQueue.hpp"
#include "../jobs/PromiseJob.hpp"
#include "../utils/Metrics.hpp"
class ThreadPool {
private:
    std::vector<std::thread> workers;
    BlockingQueue queue;
   
public:
     Metrics metrics;
    ThreadPool(int n) {
        for (int i = 0; i < n; i++) {
            workers.emplace_back([this]() {
                while (true) {
                    auto job = queue.pop();
                    if (!job) break;

                    try {
                        job->run();
                         metrics.tasksCompleted++;
                    } catch (...) {
                       metrics.tasksFailed++;
                    }
                }
            });
        }
    }

    ~ThreadPool() {
        queue.shutdown();
        for (auto& t : workers) {
            t.join();
        }
    }

    std::future<JobResult> submit(std::unique_ptr<Job> job) {
         metrics.tasksSubmitted++;

        std::promise<JobResult> prom;
        std::future<JobResult> fut = prom.get_future();

        auto wrapped = std::make_unique<PromiseJob>(std::move(job), std::move(prom));

        queue.push(std::move(wrapped));

        return fut;
    }
};