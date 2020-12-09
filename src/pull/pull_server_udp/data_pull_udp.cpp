#include "data_pull_udp.h"
#include "static_unit.h"
#include "udp_pull_server.h"

DataPullUdp::DataPullUdp() {
    start();
}

void DataPullUdp::start() {
    server_thread = std::make_shared<std::thread>(listener, default_pull_port);
}

void DataPullUdp::listener(unsigned short port) {
    auto io_context = std::make_shared<asio::io_context>();
    StaticUnit::io_context_queue.enqueue(io_context);
    auto udp_pull_server = std::make_shared<UdpPullServer>(*io_context, port);

    io_context->run();
}

DataPullUdp::~DataPullUdp() {
    server_thread->join();
    spdlog::info("Udp pull destroy.");
    StaticUnit::log->daily->info("Udp pull destroy.");
    StaticUnit::log->daily->flush();
}
