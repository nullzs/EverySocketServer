#include "static_unit.h"
#include "listener_config.h"
#include <memory>
#include <stdexcept>
#include <vector>

using std::logic_error;
using JsonArray = rapidjson::Document::Array;

const std::vector<std::string> keys{"type", "tcp_port", "udp_port", "name"};

void ListenerConfig::get_listener_config(const char *file_name) {
    StaticUnit::log->daily->info("listener file:{}", file_name);

    bool file_exist{true};
    //get file
    std::ifstream in{std::move(get_file(file_name, &file_exist))};

    if (file_exist) {
        try {
            //file io deleter
            std::shared_ptr<std::ifstream> file_close(&in, [](std::ifstream *p) {
                p->close();
            });

            std::string json_content((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
            rapidjson::Document document;
            std::shared_ptr<rapidjson::Document::Array> json_array;
            check_json_data(json_content.data(),  document, json_array);

            get_listener_form_array(*json_array);


        } catch (std::exception &ec) {
            StaticUnit::log->daily->error(ec.what());
            spdlog::error(ec.what());

        }

    }
}

std::ifstream ListenerConfig::get_file(const char *file_name, bool *file_exist) {
    std::ifstream in(file_name);
    if (!in.is_open()) {
        spdlog::error("file: '{}' not exist!", file_name);
        *file_exist = false;
    }
    return in;
}

void ListenerConfig::check_json_data(const char *data,
                                     rapidjson::Document &document,
                                     std::shared_ptr<JsonArray> &json_arr) noexcept(false)  {
    document.Parse(data);
    if (!document.IsArray()) {
        throw logic_error("[ListenerConfig] Data is not a json array!");
    }

    json_arr = std::make_shared<JsonArray>(document.GetArray());
    if (json_arr->Empty()) {
        throw logic_error("[ListenerConfig] json_arr is empty!");
    }
}

void ListenerConfig::get_listener_form_array( const JsonArray &json_array) noexcept(false) {
    for(const auto &node: json_array) {
        if (!node.IsObject()) {
            throw logic_error("[ListenerConfig] Json array's child is not a object!");
        }
        auto json_obj = node.GetObject();

        //check key
        for(const auto &key: keys) {
            if (!json_obj.HasMember(key.data())) {
                throw logic_error("[ListenerConfig] A json object haven't key:" + key);
            }
        }
        //check key type (simple)
        for(const auto &key: keys) {
            if (key != "name") {
                if(!json_obj.FindMember(key.data())->value.IsInt()){
                    throw logic_error("[ListenerConfig] A json object key:" + key + " is not a number");
                }
            }else {
                if(!json_obj.FindMember(key.data())->value.IsString()){
                    throw logic_error("[ListenerConfig] A json object key:" + key + " is not a string");
                }
            }
        }

        int type = json_obj.FindMember("type")->value.GetInt();
        //tcp or udp port should in area: 0~65535 (unsigned short)
        unsigned short tcp_port = static_cast<unsigned short>(json_obj.FindMember("tcp_port")->value.GetUint());
        unsigned short udp_port = static_cast<unsigned short>(json_obj.FindMember("udp_port")->value.GetUint());
        std::string name = json_obj.FindMember("name")->value.GetString();

        //show
        spdlog::info("type:{}, tcp: {}, udp: {}, name: {}", type, tcp_port, udp_port, name);
        //insert to StaticUnit
    }
}