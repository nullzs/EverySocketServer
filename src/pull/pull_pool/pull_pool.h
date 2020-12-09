#ifndef EVERYSOCKETSERVER_PULL_POOL_H
#define EVERYSOCKETSERVER_PULL_POOL_H

#include <vector>
#include <thread>
#include <memory>

class PullPool {
public:
    explicit PullPool(int thread_count);
    PullPool() = delete;

    ~PullPool();

private:
    void make_pool(int thread_count);

    std::vector<std::shared_ptr<std::thread> > pull_threads;

};


#endif //EVERYSOCKETSERVER_PULL_POOL_H
