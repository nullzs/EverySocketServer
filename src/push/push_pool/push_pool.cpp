#include "push_pool.h"
#include "spdlog/spdlog.h"

PushPool::PushPool(int thread_count, int type) {
    make_pool(thread_count, type);
}

PushPool::~PushPool() {
    int count{0};
    for (const auto &push_thread: push_threads) {
        push_thread->join();
        spdlog::info("push pool remove: {}", count);
    }
    push_threads.clear();
}

void PushPool::make_pool(int thread_count, int type) {
    for (int i = 0; i < thread_count; i++) {
        auto push_thread = std::make_shared<std::thread>(PushTask::do_task, type);
        push_threads.push_back(push_thread);
        spdlog::info("push pool add: {}", i);
    }
}
