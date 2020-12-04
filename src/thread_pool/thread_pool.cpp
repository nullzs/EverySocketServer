#include "thread_pool.h"
#include "thread_task.h"
#include "spdlog/spdlog.h"

ThreadPool::ThreadPool(int thread_count) :thread_count_(thread_count) {
    create_thread_pool();
}

ThreadPool::~ThreadPool() {
    int num{0};
    for(auto &task_thread: threads_) {
        task_thread->join();
        spdlog::info("thread: {} join", num++);
    }
    threads_.clear();
}

void ThreadPool::create_thread_pool()  {
    for (int i=0; i< thread_count_; i++) {
        auto task_thread = std::make_shared<std::thread>(ThreadTask::do_task, i);
        threads_.push_back(task_thread);
    }
}
