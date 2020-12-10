#include "static_unit.h"

std::shared_ptr<LogFile> StaticUnit::log;

std::shared_ptr<std::vector<ListenerType> > StaticUnit::listener_conf_list;
std::mutex StaticUnit::listener_conf_list_mutex;

// map<ip+port, session> like: map<"121.22.123.123:17652", session>
std::shared_ptr<std::unordered_map<std::string, std::shared_ptr<TcpSession> > > StaticUnit::tcp_session_map;
std::mutex StaticUnit::tcp_session_map_mutex;

std::atomic_bool StaticUnit::destroy_flag;

std::condition_variable StaticUnit::data_queue_wait_condition;
std::mutex StaticUnit::data_queue_wait_mutex;
std::shared_ptr<moodycamel::ConcurrentQueue<ReceiveData> > StaticUnit::data_queue;

std::condition_variable StaticUnit::push_queue_wait_condition;
std::mutex StaticUnit::push_queue_wait_mutex;
std::shared_ptr<moodycamel::ConcurrentQueue<std::string> > StaticUnit::push_queue;

moodycamel::ConcurrentQueue< std::shared_ptr<asio::io_context> > StaticUnit::io_context_queue;

std::condition_variable StaticUnit::pull_queue_wait_condition;
std::mutex StaticUnit::pull_queue_wait_mutex;
std::shared_ptr<moodycamel::ConcurrentQueue<std::string> > StaticUnit::pull_queue;
