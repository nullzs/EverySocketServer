#include "static_unit.h"

std::shared_ptr<LogFile> StaticUnit::log;

std::shared_ptr<std::vector<ListenerType> > StaticUnit::listener_conf_list;
std::mutex StaticUnit::listener_conf_list_mutex;
