#include "pull_task.h"
#include "static_unit.h"

void PullTask::do_task() {
    std::string data;
    while (!StaticUnit::destroy_flag.load()) {
        if(StaticUnit::pull_queue->size_approx() == 0) {
            std::unique_lock<std::mutex> locker(StaticUnit::pull_queue_wait_mutex);
            StaticUnit::pull_queue_wait_condition.wait(locker);
            continue;
        }
        if(!StaticUnit::pull_queue->try_dequeue(data)) continue;
        //print pull command
        spdlog::info(data);
    }
    spdlog::info("pull task end:{}", 0);
}
