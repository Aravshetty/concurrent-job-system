#pragma once
#include <vector>
#include <thread>
#include <future>

#include "../queue/BlockingQueue.hpp"
#include "../jobs/PromiseJob.hpp"

class ThreadPool {
private:
    std::vector<std::thread> workers;
    BlockingQueue queue;

public:

    ThreadPool(int n) {
        for (int i = 0; i < n; i++) {
            workers.emplace_back([this]() {
                while (true) {
                    auto job = queue.pop();
                    if (!job) break;

                    try {
                        job->run();
                    } catch (...) {
                       
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

        std::promise<JobResult> prom;
        std::future<JobResult> fut = prom.get_future();

        auto wrapped = std::make_unique<PromiseJob>(std::move(job), std::move(prom));

        queue.push(std::move(wrapped));

        return fut;
    }
};