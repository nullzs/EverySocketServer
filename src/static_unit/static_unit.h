#ifndef EVERYSOCKETSERVER_STATIC_UNIT_H
#define EVERYSOCKETSERVER_STATIC_UNIT_H

#include <memory>
#include <vector>
#include <mutex>
#include <unordered_map>
#include <atomic>
#include <condition_variable>
#include "log_file.h"
#include "listener_type.h"
#include "tcp/tcp_session.h"
#include "concurrentqueue.h"
#include "receive_data.h"

class StaticUnit {
public:
    static std::shared_ptr<LogFile> log;

    //listeners config msg
    static std::shared_ptr<std::vector<ListenerType> > listener_conf_list;
    static std::mutex listener_conf_list_mutex;

    //tcp session
    static std::shared_ptr<std::unordered_map<std::string, std::weak_ptr<TcpSession> > > tcp_session_map;
    static std::mutex tcp_session_map_mutex;

    //thread destroy flag
    static std::atomic_bool destroy_flag;

    //shared task list: wait condition ,lock mutex and list
    static std::condition_variable data_queue_wait_condition;
    static std::mutex data_queue_wait_mutex;
    static std::shared_ptr<moodycamel::ConcurrentQueue<ReceiveData> > data_queue;
};


#endif //EVERYSOCKETSERVER_STATIC_UNIT_H
