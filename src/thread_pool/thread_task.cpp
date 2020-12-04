#include "thread_task.h"
#include "static_unit.h"

void ThreadTask::do_task(int thread_id) {
    spdlog::info("thread task :{} start", thread_id);

    while (!StaticUnit::destroy_flag.load()) {

        //Sleep and wait if queue is null
        if(StaticUnit::data_queue->size_approx() == 0) {
            std::unique_lock<std::mutex> locker(StaticUnit::data_queue_wait_mutex);
            StaticUnit::data_queue_wait_condition.wait(locker);
            continue;
        }
        ReceiveData temp_data;
        if(!StaticUnit::data_queue->try_dequeue(temp_data)) continue;

        spdlog::info("\n [{}] {} \n [data]:{}\n [time]:{}",
                     temp_data.type == ReceiveData::TCP ?"TCP": "UDP",
                     temp_data.link_data,
                     temp_data.data,
                     temp_data.timestamp
                     );
    }
    spdlog::info("thread end:{}", thread_id);
}
