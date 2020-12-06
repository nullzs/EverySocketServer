#include "push_task.h"
#include "static_unit.h"
#include "data_push.h"
#include "data_push_print.h"

void PushTask::do_task(int type) {
    std::shared_ptr<DataPush> push_obj;
    if (type == PushTask::push_default) {
        push_obj = std::make_shared<DataPushPrint>();
    }
    std::string data;
    while (!StaticUnit::destroy_flag.load()) {
        if(StaticUnit::push_queue->size_approx() == 0) {
            std::unique_lock<std::mutex> locker(StaticUnit::push_queue_wait_mutex);
            StaticUnit::push_queue_wait_condition.wait(locker);
            continue;
        }

        if(!StaticUnit::push_queue->try_dequeue(data)) continue;
        push_obj->push_data(data);
    }
    spdlog::info("push task end:{}", 0);
}
