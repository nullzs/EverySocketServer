#ifndef EVERYSOCKETSERVER_DATA_PUSH_H
#define EVERYSOCKETSERVER_DATA_PUSH_H

#include <string>
#include "receive_data.h"

class DataPush {
public:
    virtual ~DataPush() = default;
    virtual void push_data(const std::string &) = 0;
    virtual void push_receive_data(const ReceiveData &) = 0;
};


#endif //EVERYSOCKETSERVER_DATA_PUSH_H
