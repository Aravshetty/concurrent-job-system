#include <iostream>
#include "include/threadpool/ThreadPool.hpp"
#include "include/jobs/SumJob.hpp"
#include "include/jobs/PrimeJob.hpp"

int main() {

    ThreadPool pool(3);

    auto f1 = pool.submit(std::make_unique<SumJob>(1, 100));
    auto f2 = pool.submit(std::make_unique<PrimeJob>(1, 100));

    std::cout << "Waiting for results...\n";

    auto r1 = f1.get();
    auto r2 = f2.get();

    std::cout << r1.message << " -> " << r1.value << "\n";
    std::cout << r2.message << " -> " << r2.value << "\n";

    return 0;
}