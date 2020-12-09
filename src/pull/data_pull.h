#ifndef EVERYSOCKETSERVER_DATA_PULL_H
#define EVERYSOCKETSERVER_DATA_PULL_H

class DataPull {
public:
    virtual ~DataPull() = default;
    virtual void start() =0;
};


#endif //EVERYSOCKETSERVER_DATA_PULL_H
