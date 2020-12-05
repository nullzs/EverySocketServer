#ifndef EVERYSOCKETSERVER_RECEIVE_DATA_UNIT_H
#define EVERYSOCKETSERVER_RECEIVE_DATA_UNIT_H

#include <string>

class ReceiveData {
public:
    ReceiveData() = default;

    ReceiveData(int sock_type_in, long long timestamp_in, int type_in,
                std::string addr_in, unsigned short port_in, std::string &data_in)
            : sock_type(sock_type_in), timestamp(timestamp_in)
            , type(type_in), addr(std::move(addr_in)), port(port_in),
              data(std::move(data_in)) {}

    enum {
        TCP = 0,
        UDP = 1
    };
    int sock_type; //TCP or UDP
    long long timestamp;

    int type;
    std::string addr;
    unsigned short port;
    std::string data;
};


#endif //EVERYSOCKETSERVER_RECEIVE_DATA_UNIT_H
