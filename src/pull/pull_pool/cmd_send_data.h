#ifndef EVERYSOCKETSERVER_CMD_SEND_DATA_H
#define EVERYSOCKETSERVER_CMD_SEND_DATA_H

#include <string>

class CmdSendData {
public:
    std::string addr, bytes_data;
    unsigned short port{0};
    int sock_type{-1};
    unsigned int serial_num{0};

    void clean(){
        addr.clear();
        bytes_data.clear();
        port = 0;
        sock_type = -1;
        serial_num = 0;
    }

    enum {
        TCP = 0,
        UDP = 1
    };


};


#endif //EVERYSOCKETSERVER_CMD_SEND_DATA_H
