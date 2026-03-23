#pragma once
#include <atomic>

struct Metrics {
    std::atomic<int> tasksSubmitted{0};
    std::atomic<int> tasksCompleted{0};
    std::atomic<int> tasksFailed{0};
};