#pragma once
#include <queue>
#include <memory>
#include <mutex>

#include "../core/Job.hpp"

class JobQueue{
  private:
    std::queue<std::unique_ptr<Job>> q;
    std::mutex m;
  public:
    void push(std::unique_ptr<Job> job){
      std::lock_guard<std::mutex> lock(m);
       q.push(std::move(job));

    }
    std::unique_ptr<Job> tryPop() {
        std::lock_guard<std::mutex> lock(m);

        if (q.empty()) {
            return nullptr;
        }

        auto job = std::move(q.front());
        q.pop();
        return job;
    }

};