#include "udp_pull_server.h"
#include "static_unit.h"

UdpPullServer::UdpPullServer(asio::io_context &io_context, unsigned short port)
        : server_socket_(io_context, asio::ip::udp::endpoint(asio::ip::udp::v4(), port)){
    do_receive();
}

void UdpPullServer::do_receive() {
    server_socket_.async_receive_from(asio::buffer(data_, max_length), sender_endpoint_,
                                      [this](std::error_code ec, std::size_t byte_receive) {
                                          this->receive_handle(ec, byte_receive);
                                          do_receive();
                                      });
}

void UdpPullServer::receive_handle(std::error_code &ec, size_t byte_receive) {
    if (!ec && byte_receive > 0) {
        std::string str(data_, byte_receive);
        spdlog::info("udp cmd:{}", str);
        StaticUnit::pull_queue->enqueue(std::move(str));
        StaticUnit::pull_queue_wait_condition.notify_all();
    }
}
