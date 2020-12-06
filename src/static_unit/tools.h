#ifndef EVERYSOCKETSERVER_TOOLS_H
#define EVERYSOCKETSERVER_TOOLS_H

#include <chrono>
#include <string>
#include "receive_data.h"

class Tools {
public:
    static inline long long get_now() {
        return std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::system_clock::now().time_since_epoch()).count();
    }

    static void convert_hex(std::string &str);

    static void serialize_receive(std::string &ret, const ReceiveData &receive_data);

    static void destroy_thread(const std::string &event, const std::string &platform);
};


#endif //EVERYSOCKETSERVER_TOOLS_H
