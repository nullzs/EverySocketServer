#ifndef EVERYSOCKETSERVER_PUSH_POOL_H
#define EVERYSOCKETSERVER_PUSH_POOL_H

#include <thread>
#include <vector>
#include <memory>
#include "push_task.h"

class PushPool {
public:
    explicit PushPool(int thread_count, int type);
    PushPool() = delete;
    PushPool(const PushPool&) = delete;
    PushPool & operator=(const PushPool&) = delete;
    virtual ~PushPool();

private:
    std::vector<std::shared_ptr<std::thread> > push_threads;

    void make_pool(int thread_count, int type);
};


#endif //EVERYSOCKETSERVER_PUSH_POOL_H
