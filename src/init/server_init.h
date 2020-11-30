// Created on 2020/11/30.

#ifndef EVERY_SOCKET_SERVER_SERVER_INIT_H
#define EVERY_SOCKET_SERVER_SERVER_INIT_H
#include <atomic>

//single-init-object
class ServerInit {
public:
    virtual ~ServerInit() = default;
    ServerInit& operator=(const ServerInit&) = delete;
    ServerInit(const ServerInit&) = delete;
    static ServerInit& get_instance() {
        static ServerInit server_init;
        return server_init;
    }
    void init();
private:
    ServerInit() {is_init.store(false);};
    static std::atomic_bool is_init;
};


#endif //EVERY_SOCKET_SERVER_SERVER_INIT_H
