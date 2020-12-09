#ifndef EVERYSOCKETSERVER_UDP_PULL_SERVER_H
#define EVERYSOCKETSERVER_UDP_PULL_SERVER_H

#include "socket_server.h"
#include "asio.hpp"

class UdpPullServer : SocketServer {
public:
    UdpPullServer(asio::io_context &io_context, unsigned short port);

private:
    void do_receive();
    asio::ip::udp::socket server_socket_;
    asio::ip::udp::endpoint sender_endpoint_;
    enum {
        max_length = 1024
    };
    char data_[max_length]{0};

    void receive_handle(std::error_code &ec, size_t byte_receive);
};


#endif //EVERYSOCKETSERVER_UDP_PULL_SERVER_H
