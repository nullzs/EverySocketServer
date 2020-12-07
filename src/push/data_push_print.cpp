#include "data_push_print.h"
#include "spdlog/spdlog.h"

void DataPushPrint::push_data(const std::string &msg) {
    spdlog::info(msg);
}
