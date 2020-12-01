#include "server_init.h"
#include "static_unit.h"
#include "listener_config.h"

std::atomic_bool ServerInit::is_init;

void ServerInit::init() {
    if(is_init.exchange(true)) return;

    //init static unit data init
    init_static_value();

    //init listener config
    ListenerConfig::get_listener_config();
}

void ServerInit::init_static_value() {
    //init log
    StaticUnit::log = std::make_shared<LogFile>();

    {
        std::lock_guard<std::mutex> locker(StaticUnit::listener_conf_list_mutex);
        StaticUnit::listener_conf_list = std::make_shared<std::vector<ListenerType> >();
    }

}
