#include "thread_task.h"
#include "static_unit.h"
#include "tools.h"

void ThreadTask::do_task(int thread_id) {
    spdlog::info("thread task :{} start", thread_id);
    ReceiveData temp_data;
    std::string temp_str_data;
    while (!StaticUnit::destroy_flag.load()) {

        //Sleep and wait if queue is null
        if(StaticUnit::data_queue->size_approx() == 0) {
            std::unique_lock<std::mutex> locker(StaticUnit::data_queue_wait_mutex);
            StaticUnit::data_queue_wait_condition.wait(locker);
            continue;
        }

        if(!StaticUnit::data_queue->try_dequeue(temp_data)) continue;
        Tools::serialize_receive(temp_str_data, temp_data);

        StaticUnit::push_queue->enqueue(std::move(temp_str_data));
        StaticUnit::push_queue_wait_condition.notify_one();

    }
    spdlog::info("thread end:{}", thread_id);
}
