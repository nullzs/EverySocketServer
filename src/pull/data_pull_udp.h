#ifndef EVERYSOCKETSERVER_DATA_PULL_UDP_H
#define EVERYSOCKETSERVER_DATA_PULL_UDP_H

#include "data_pull.h"

class DataPullUdp : public DataPull{
public:
    ~DataPullUdp() override = default;
    void start() override;
};


#endif //EVERYSOCKETSERVER_DATA_PULL_UDP_H
