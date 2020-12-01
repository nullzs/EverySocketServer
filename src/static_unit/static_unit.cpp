#include "static_unit.h"

std::shared_ptr<LogFile> StaticUnit::log;

std::shared_ptr<std::vector<ListenerType> > StaticUnit::listener_conf_list;
std::mutex StaticUnit::listener_conf_list_mutex;

// map<ip+port, session> like: map<"121.22.123.123:17652", session>
std::shared_ptr<std::unordered_map<std::string, std::weak_ptr<TcpSession> > > StaticUnit::tcp_session_map;
std::mutex StaticUnit::tcp_session_map_mutex;