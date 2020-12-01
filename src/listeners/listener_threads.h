#ifndef EVERYSOCKETSERVER_LISTENER_THREADS_H
#define EVERYSOCKETSERVER_LISTENER_THREADS_H

#include <memory>
#include <thread>
#include <vector>

class ListenerThreads {
public:
    ListenerThreads();
    ~ListenerThreads();

    ListenerThreads(const ListenerThreads&) = delete;
    ListenerThreads & operator=(const ListenerThreads &) = delete;

    enum {
        TCP_SOCK=0, UDP_SOCK=1
    };

private:
    void join_thread();
    void init();
    std::vector<std::shared_ptr<std::thread> > thread_list;

    static void listen_thread(unsigned short port, int sock_type, int type);
};


#endif //EVERYSOCKETSERVER_LISTENER_THREADS_H
