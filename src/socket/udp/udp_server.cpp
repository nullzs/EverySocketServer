
#include "udp_server.h"
#include "tools.h"
#include "static_unit.h"

UdpServer::UdpServer(asio::io_context &io_context, unsigned short port, int type)
        : server_socket_(io_context, asio::ip::udp::endpoint(asio::ip::udp::v4(), port)), type_(type) {
    do_receive();
}

void UdpServer::do_receive() {
    server_socket_.async_receive_from(asio::buffer(data_, max_length), sender_endpoint_,
                                      [this](std::error_code ec, std::size_t byte_receive) {
                                          this->receive_handle(ec, byte_receive);
                                          do_receive();
                                      });
}

void UdpServer::receive_handle(std::error_code &ec, std::size_t byte_receive) {
    if (!ec && byte_receive > 0) {
        auto now = Tools::get_now();
        std::string str(data_, byte_receive);

        Tools::convert_hex(str);

        ReceiveData receive_data(ReceiveData::UDP, now, type_,
                                 sender_endpoint_.address().to_string(),
                                 sender_endpoint_.port(), str);
        StaticUnit::data_queue->enqueue(std::move(receive_data));
        StaticUnit::data_queue_wait_condition.notify_all();
    }
}