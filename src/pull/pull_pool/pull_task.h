#ifndef EVERYSOCKETSERVER_PULL_TASK_H
#define EVERYSOCKETSERVER_PULL_TASK_H


#include <string>
#include "rapidjson/document.h"
#include "cmd_send_data.h"

class PullTask {
public:
    static void do_task();

    static void send_command(const std::string &cmd_data, rapidjson::Document &json_doc, CmdSendData &cmd_send_data);

    static bool encode_json(const std::string &cmd_data, rapidjson::Document &json_doc, CmdSendData &cmd_send_data);

    static void send_command_to_socket(const CmdSendData &cmd_send_data);
};


#endif //EVERYSOCKETSERVER_PULL_TASK_H
