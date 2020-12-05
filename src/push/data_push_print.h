#ifndef EVERYSOCKETSERVER_DATA_PUSH_PRINT_H
#define EVERYSOCKETSERVER_DATA_PUSH_PRINT_H

#include "data_push.h"

//only use to test
class DataPushPrint : public DataPush{
public:
    void push_data(const std::string &) override;
    void push_receive_data(const ReceiveData &) override;

};


#endif //EVERYSOCKETSERVER_DATA_PUSH_PRINT_H
