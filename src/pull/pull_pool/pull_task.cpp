#include "static_unit.h"
#include "pull_task.h"

void PullTask::do_task() {
    std::string cmd_data;
    rapidjson::Document json_doc;
    CmdSendData cmd_send_data;
    while (!StaticUnit::destroy_flag.load()) {
        if (StaticUnit::pull_queue->size_approx() == 0) {
            std::unique_lock<std::mutex> locker(StaticUnit::pull_queue_wait_mutex);
            StaticUnit::pull_queue_wait_condition.wait(locker);
            continue;
        }
        if (!StaticUnit::pull_queue->try_dequeue(cmd_data)) continue;
        //print pull command
        send_command(cmd_data, json_doc, cmd_send_data);
    }
    spdlog::info("pull task end:{}", 0);
}

void PullTask::send_command(const std::string &cmd_data, rapidjson::Document &json_doc, CmdSendData &cmd_send_data) {

    cmd_send_data.clean();
    //encode json
    if (!encode_json(cmd_data, json_doc, cmd_send_data)) {
        spdlog::error("pull data is a invalid common json:{}", cmd_data);
        return;
    }
    send_command_to_socket(cmd_send_data);
}

bool PullTask::encode_json(const std::string &cmd_data, rapidjson::Document &json_doc, CmdSendData &cmd_send_data) {

    if (json_doc.Parse(cmd_data.c_str()).HasParseError()) return false;
    if (!json_doc.IsObject()) return false;

    if (!(json_doc.HasMember("addr") && json_doc["addr"].IsString())) return false;
    if (!(json_doc.HasMember("bytes_data") && json_doc["bytes_data"].IsString())) return false;

    if (!(json_doc.HasMember("serial_num") && json_doc["serial_num"].IsUint())) return false;
    if (!(json_doc.HasMember("port") && json_doc["port"].IsUint())) return false;
    if (!(json_doc.HasMember("sock_type") && json_doc["sock_type"].IsInt())) return false;

    cmd_send_data.addr = json_doc["addr"].GetString();
    cmd_send_data.bytes_data = json_doc["bytes_data"].GetString();
    cmd_send_data.serial_num = json_doc["serial_num"].GetUint();

    cmd_send_data.port = static_cast<unsigned short>(json_doc["port"].GetUint());
    cmd_send_data.sock_type = json_doc["sock_type"].GetInt();

    return true;
}


void PullTask::send_command_to_socket(const CmdSendData &cmd_send_data) {
    spdlog::info("send to [{}] {}:{}, bytes_data:[{}]",
                 cmd_send_data.sock_type == CmdSendData::TCP ? "TCP": "UDP",
                 cmd_send_data.addr, cmd_send_data.port, cmd_send_data.bytes_data);
    if (cmd_send_data.sock_type == CmdSendData::TCP) {
        std::string link_str = cmd_send_data.addr + ":" + std::to_string(cmd_send_data.port);
        std::shared_ptr<TcpSession> session;
        bool tcp_session_exist{false};
        //send tcp
        {
            std::unique_lock<std::mutex> locker(StaticUnit::tcp_session_map_mutex);
            auto item = StaticUnit::tcp_session_map->find(link_str);
            if(item != StaticUnit::tcp_session_map->end()){
                tcp_session_exist = true;
                session = item->second;
            }
        }
        if(tcp_session_exist) {
            //send to socket
            session->write(cmd_send_data.bytes_data, cmd_send_data.serial_num);
        }
    }else {
        //send udp
    }
}