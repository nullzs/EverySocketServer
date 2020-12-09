#ifndef EVERYSOCKETSERVER_DATA_PULL_UDP_H
#define EVERYSOCKETSERVER_DATA_PULL_UDP_H

#include "data_pull.h"
#include <memory>
#include <thread>

class DataPullUdp : public DataPull {
public:
    DataPullUdp();

    DataPullUdp(const DataPullUdp &) = delete;

    ~DataPullUdp() override;

    DataPullUdp &operator=(const DataPullUdp &) = delete;

    void start() override;

private:
    std::shared_ptr<std::thread> server_thread;

    static void listener(unsigned short port);

    enum {
        default_pull_port = 12300
    };
};


#endif //EVERYSOCKETSERVER_DATA_PULL_UDP_H
