#include "server_init.h"
#include "static_unit.h"
#include "listener_config.h"

std::atomic_bool ServerInit::is_init;

void ServerInit::init() {
    if(is_init.exchange(true)) return;
    //init log
    StaticUnit::log = std::make_shared<LogFile>();
    //init listener config
    ListenerConfig::get_listener_config();
}
