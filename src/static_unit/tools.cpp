#include "tools.h"
#include "static_unit.h"
#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include <sstream>
#include <iomanip>

void Tools::convert_hex(std::string &str) {
    std::ostringstream result;
    for (unsigned char val: str) {
        result << std::uppercase << std::setw(2) << std::setfill('0') << std::hex << static_cast<unsigned short>(val);
    }
    str = std::move(result.str());
}

void Tools::convert_hex_to_str(std::string &str){
    std::stringstream  result;
    std::string temp(str.size()/2, '0');
    int temp_num{0};
    int count = static_cast<int>(str.size()/2);

    for(int i=0; i< count; i++) {

        result << str.substr(2*i, 2);
        result >> std::hex>> temp_num;
        result.clear();
        temp.at(i) = static_cast<unsigned char>(temp_num);
    }
    swap(temp, str);
}

void Tools::serialize_receive(std::string &ret, ReceiveData &receive_data) {

    Tools::convert_hex(receive_data.data);
    rapidjson::StringBuffer buffer;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
    writer.StartObject();

    writer.Key("type");
    writer.Int(receive_data.type);

    writer.Key("addr");
    writer.String(receive_data.addr.data());

    writer.Key("port");
    writer.Uint(receive_data.port);

    writer.Key("sock_type");
    writer.Int(receive_data.sock_type);

    writer.Key("data");
    writer.String(receive_data.data.data());

    writer.Key("timestamp");
    writer.Int64(receive_data.timestamp);

    writer.EndObject();

    ret = buffer.GetString();
}

void Tools::destroy_thread(const std::string &event, const std::string &platform) {
    StaticUnit::destroy_flag.store(true);
    StaticUnit::data_queue_wait_condition.notify_all();
    StaticUnit::push_queue_wait_condition.notify_all();
    StaticUnit::pull_queue_wait_condition.notify_all();

    while (StaticUnit::io_context_queue.size_approx() > 0) {
        std::shared_ptr<asio::io_context> io_context;
        StaticUnit::io_context_queue.try_dequeue(io_context);
        io_context->stop();
    }

    spdlog::error(event);
    StaticUnit::log->daily->error("[{}] {}", platform, event);
    StaticUnit::log->daily->flush();

}


std::string Tools::get_convert_hex(const std::string &str) {
    std::ostringstream result;
    for (unsigned char val: str) {
        result << std::uppercase << std::setw(2) << std::setfill('0') << std::hex << static_cast<unsigned short>(val);
    }
    return std::move(result.str());
}

std::string Tools::get_convert_hex_to_str(const std::string &str){
    std::stringstream  result;
    std::string temp(str.size()/2, '0');
    int temp_num{0};
    int count = static_cast<int>(str.size()/2);

    for(int i=0; i< count; i++) {

        result << str.substr(2*i, 2);
        result >> std::hex>> temp_num;
        result.clear();
        temp.at(i) = static_cast<unsigned char>(temp_num);
    }
    return temp;
}