#ifndef EVERYSOCKETSERVER_LISTENER_TYPE_H
#define EVERYSOCKETSERVER_LISTENER_TYPE_H

#include <string>
#include <utility>

struct ListenerType {
    ListenerType(int type_in, unsigned short tcp_port_in,
                 unsigned short udp_port_in, std::string name_in)
                 : type(type_in)
                 , tcp_port(tcp_port_in)
                 , udp_port(udp_port_in)
                 , name(std::move(name_in)){}

    int type{0};
    unsigned short tcp_port{0};
    unsigned short udp_port{0};
    std::string name;

};


#endif //EVERYSOCKETSERVER_LISTENER_TYPE_H
