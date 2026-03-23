#pragma once
#include "../core/Job.hpp"
#include <future> 

class PromiseJob : public Job {
private:
    std::unique_ptr<Job> actualJob;
    std::promise<JobResult> prom;

public:
    PromiseJob(std::unique_ptr<Job> job, std::promise<JobResult> p)
        : actualJob(std::move(job)), prom(std::move(p)) {}

    JobResult run() override {
        try {
            JobResult res = actualJob->run();
            prom.set_value(res); // send result
            return res;
        } catch (...) {
            prom.set_exception(std::current_exception());
            throw;
        }
    }
};
