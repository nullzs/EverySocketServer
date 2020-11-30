#ifndef EVERYSOCKETSERVER_LISTENER_CONFIG_H
#define EVERYSOCKETSERVER_LISTENER_CONFIG_H

#include <fstream>
#include <memory>
#include <rapidjson/document.h>

class ListenerConfig {
public:
    static void get_listener_config(const char *file_name = "./socket.json");

private:
    ListenerConfig() = default;

    static std::ifstream get_file(const char *file_name, bool *file_exist);

    static void check_json_data(const char *data, rapidjson::Document &document,
                                std::shared_ptr<rapidjson::Document::Array> &json_arr);

    static void get_listener_form_array(const rapidjson::Document::Array & json_array);
};

/**
 * file example:
 * [{
    "type": 1,
    "tcp_port": 7788,
    "udp_port": 7788,
    "name": "protocol-1"
  },
  {
    "type": 2,
    "tcp_port": 7777,
    "udp_port": 7777,
    "name": "protocol-2"
  }]
 *
 */


#endif //EVERYSOCKETSERVER_LISTENER_CONFIG_H
