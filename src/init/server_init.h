#ifndef EVERYSOCKETSERVER_SERVER_INIT_H
#define EVERYSOCKETSERVER_SERVER_INIT_H
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
    static std::atomic_bool is_init;

    ServerInit() {is_init.store(false);};
    void init_static_value();
};


#endif //EVERYSOCKETSERVER_SERVER_INIT_H
