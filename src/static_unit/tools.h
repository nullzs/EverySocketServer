#ifndef EVERYSOCKETSERVER_TOOLS_H
#define EVERYSOCKETSERVER_TOOLS_H
#include <chrono>
#include <string>

class Tools {
public:
    static inline long long get_now() {
        return std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::system_clock::now().time_since_epoch()).count();
    }

    static void convert_hex(std::string &str);
};


#endif //EVERYSOCKETSERVER_TOOLS_H
