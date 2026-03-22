#pragma once
#include "../core/Job.hpp"
#include <thread>
#include <chrono>

class SleepJob:public Job{
   private:
    int seconds;
   public:
     SleepJob(int s) : seconds(s) {}
     JobResult run() override{
       std::this_thread::sleep_for(std::chrono::seconds(seconds));
        return {true, "Slept successfully", seconds};

     }
     int priority() const override {
        return 0;
    }
};