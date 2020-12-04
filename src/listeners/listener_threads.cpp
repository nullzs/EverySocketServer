#include "listener_threads.h"
#include "static_unit.h"
#include <thread>
#include <string>
#include "tcp/tcp_server.h"
#include "udp/udp_server.h"

ListenerThreads::ListenerThreads() {
    init();
}

void ListenerThreads::init() {
    //create threads to listen port;
    {
        std::lock_guard<std::mutex> locker(StaticUnit::listener_conf_list_mutex);
        for (const auto &item: *StaticUnit::listener_conf_list) {
            //make thread
            auto sock_thread_tcp = std::make_shared<std::thread>(listen_thread, item.tcp_port, TCP_SOCK, item.type);
            thread_list.push_back(sock_thread_tcp);

            auto sock_thread_udp = std::make_shared<std::thread>(listen_thread, item.udp_port, UDP_SOCK, item.type);
            thread_list.push_back(sock_thread_udp);
        }
    }
}

void ListenerThreads::listen_thread(unsigned short port, int sock_type, int type) {
    spdlog::info("Thread-msg port: {}, sock_type: {}, type: {}", port, sock_type, type);
    asio::io_context io_context;
    std::shared_ptr<SocketServer> server;
    std::string sock_type_str = sock_type == TCP_SOCK ? "TCP" : "UDP";

    if(TCP_SOCK == sock_type) {
        server = std::make_shared<TcpServer>(io_context, port, type);
    } else if(UDP_SOCK == sock_type) {
        server = std::make_shared<UdpServer>(io_context, port, type);
    }

    spdlog::info("Listen {} : {}", sock_type_str, port);
    io_context.run();
}

ListenerThreads::~ListenerThreads() {
    join_thread();
}

void ListenerThreads::join_thread() {
    int num{0};
    for (const auto &item: thread_list) {
        item->join();
        spdlog::info("destroy thread :{}", num++);
    }
    thread_list.clear();
}
