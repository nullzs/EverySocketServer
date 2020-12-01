#ifndef EVERYSOCKETSERVER_STATIC_UNIT_H
#define EVERYSOCKETSERVER_STATIC_UNIT_H

#include <memory>
#include <vector>
#include <mutex>
#include <unordered_map>
#include "log_file.h"
#include "listener_type.h"
#include "tcp/tcp_session.h"

class StaticUnit {
public:
    static std::shared_ptr<LogFile> log;

    static std::shared_ptr<std::vector<ListenerType> > listener_conf_list;
    static std::mutex listener_conf_list_mutex;

    static std::shared_ptr<std::unordered_map<std::string, std::weak_ptr<TcpSession> > > tcp_session_map;
    static std::mutex tcp_session_map_mutex;

};


#endif //EVERYSOCKETSERVER_STATIC_UNIT_H
