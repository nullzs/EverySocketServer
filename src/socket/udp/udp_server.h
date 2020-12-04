#ifndef EVERYSOCKETSERVER_UDP_SERVER_H
#define EVERYSOCKETSERVER_UDP_SERVER_H

#include "asio.hpp"
#include "socket_server.h"

class UdpServer : public SocketServer {
public:
    UdpServer(asio::io_context &io_context, unsigned short port, int type);

private:
    void do_receive();
    asio::ip::udp::socket server_socket_;
    asio::ip::udp::endpoint sender_endpoint_;
    enum {
        max_length = 1024
    };
    char data_[max_length];
    int type_;

    void receive_handle(std::error_code &ec, size_t byte_receive);
};


#endif //EVERYSOCKETSERVER_UDP_SERVER_H
