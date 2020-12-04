#ifndef EVERYSOCKETSERVER_RECEIVE_DATA_UNIT_H
#define EVERYSOCKETSERVER_RECEIVE_DATA_UNIT_H
#include <string>

class ReceiveData {
public:
    ReceiveData() = default;
    ReceiveData(long long timestamp_in, int type_in,
                std::string &link_data, std::string &data_in)
                : timestamp(timestamp_in)
                , type(type_in)
                , link_data(std::move(link_data))
                , data(std::move(data_in))
                {}

    long long timestamp;
    enum {
        TCP=0,
        UDP=1
    };
    int type;
    std::string link_data;
    std::string data;
};


#endif //EVERYSOCKETSERVER_RECEIVE_DATA_UNIT_H
