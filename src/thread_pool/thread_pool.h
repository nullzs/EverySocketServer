#ifndef EVERYSOCKETSERVER_THREAD_POOL_H
#define EVERYSOCKETSERVER_THREAD_POOL_H

#include <thread>
#include <memory>
#include <vector>

class ThreadPool {
public:
    explicit ThreadPool(int thread_count = 10);

    ~ThreadPool();

    ThreadPool(const ThreadPool &) = delete;
    ThreadPool &operator=(const ThreadPool &) = delete;

private:
    int thread_count_;
    std::vector<std::shared_ptr<std::thread> > threads_;

    void create_thread_pool();

};


#endif //EVERYSOCKETSERVER_THREAD_POOL_H
