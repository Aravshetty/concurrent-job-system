#pragma once
#include <queue>
#include <memory>
#include <mutex>
#include <condition_variable>

#include "../core/Job.hpp"

class BlockingQueue {
private:
    std::queue<std::unique_ptr<Job>> q;
    std::mutex m;
    std::condition_variable cv;
    bool stopped = false;

public:

    void push(std::unique_ptr<Job> job) {
        {
            std::lock_guard<std::mutex> lock(m);
            q.push(std::move(job));
        }
        cv.notify_one(); // wake one waiting thread
    }

    std::unique_ptr<Job> pop() {
        std::unique_lock<std::mutex> lock(m);

        cv.wait(lock, [this]() {
            return !q.empty() || stopped;
        });

        if (stopped && q.empty()) {
            return nullptr;
        }

        auto job = std::move(q.front());
        q.pop();
        return job;
    }

    void shutdown() {
        {
            std::lock_guard<std::mutex> lock(m);
            stopped = true;
        }
        cv.notify_all();
    }
};