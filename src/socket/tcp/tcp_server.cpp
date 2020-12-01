#include "tcp_server.h"
#include "tcp_session.h"
#include "static_unit.h"

using asio::ip::tcp;

TcpServer::TcpServer(asio::io_context &io_context, unsigned short port, int type)
        : acceptor_(io_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port)), type_(type) {
    do_accept();
}

void TcpServer::do_accept() {
    acceptor_.async_accept([this](std::error_code ec, tcp::socket socket) {
        if (!ec) {
            auto session = std::make_shared<TcpSession>(std::move(socket), type_);
            {
                std::lock_guard<std::mutex> locker(StaticUnit::tcp_session_map_mutex);
                StaticUnit::tcp_session_map->insert(std::make_pair(session->get_link(), session));
            }
            session->start();
            do_accept();
        }
    });
}
