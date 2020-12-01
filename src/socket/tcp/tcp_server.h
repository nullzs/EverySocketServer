#ifndef EVERYSOCKETSERVER_TCP_SERVER_H
#define EVERYSOCKETSERVER_TCP_SERVER_H

#include "socket_server.h"
#include "asio.hpp"

class TcpServer : public SocketServer {
public:
    TcpServer(asio::io_context &io_context, unsigned short port, int type);

    void do_accept();
private:
    asio::ip::tcp::acceptor acceptor_;
    int type_;
};


#endif //EVERYSOCKETSERVER_TCP_SERVER_H
