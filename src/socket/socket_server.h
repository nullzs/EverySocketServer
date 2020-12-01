#ifndef EVERYSOCKETSERVER_SOCKET_SERVER_H
#define EVERYSOCKETSERVER_SOCKET_SERVER_H

class SocketServer {
public:
    SocketServer()= default;
    virtual ~SocketServer() = default;
    SocketServer(const SocketServer &) = delete;
    SocketServer &operator=(const SocketServer &) = delete;
};


#endif //EVERYSOCKETSERVER_SOCKET_SERVER_H
