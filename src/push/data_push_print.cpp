#include "data_push_print.h"
#include "spdlog/spdlog.h"
#include "tools.h"

void DataPushPrint::push_data(const std::string &msg) {
    spdlog::info(msg);
}

void DataPushPrint::push_receive_data(const ReceiveData &receive_data) {
    std::string str;
    Tools::serialize_receive(str, receive_data);
    push_data(str);
}
