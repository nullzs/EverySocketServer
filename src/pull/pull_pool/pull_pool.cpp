#include "pull_pool.h"
#include "static_unit.h"
#include "pull_task.h"

PullPool::PullPool(int thread_count){
    make_pool(thread_count);
}

void PullPool::make_pool(int thread_count) {
    for (int i = 0; i < thread_count; i++) {
        auto push_thread = std::make_shared<std::thread>(PullTask::do_task);
        pull_threads.push_back(push_thread);
        spdlog::info("pull pool add: {}", i);
    }
}

PullPool::~PullPool() {
    for(const auto &item: pull_threads) {
        item->join();
    }
    pull_threads.clear();
    StaticUnit::log->daily->info("PullPool destroy.");
    StaticUnit::log->daily->flush();
}
