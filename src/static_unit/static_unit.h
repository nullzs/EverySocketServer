#ifndef EVERY_SOCKET_SERVER_STATIC_UNIT_H
#define EVERY_SOCKET_SERVER_STATIC_UNIT_H

#include "log_file.h"
#include <memory>

class StaticUnit {
public:
    static std::shared_ptr<LogFile> log;

};


#endif //EVERYSOCKETSERVER_STATIC_UNIT_H
