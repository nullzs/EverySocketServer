#ifndef EVERYSOCKETSERVER_STATIC_UNIT_H
#define EVERYSOCKETSERVER_STATIC_UNIT_H

#include <memory>
#include <vector>
#include <mutex>
#include "log_file.h"
#include "listener_type.h"

class StaticUnit {
public:
    static std::shared_ptr<LogFile> log;

    static std::shared_ptr<std::vector<ListenerType> > listener_conf_list;
    static std::mutex listener_conf_list_mutex;
};


#endif //EVERYSOCKETSERVER_STATIC_UNIT_H
