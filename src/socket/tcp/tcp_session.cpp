#include "tcp_session.h"
#include "static_unit.h"
#include "tools.h"
#include "decoder_tools.h"


TcpSession::TcpSession(asio::ip::tcp::socket socket, int type)
        : socket_(std::move(socket))
        , type_(type)
        , decoder(DecoderTools::get_decoder(type))
{
    set_link_value();
}

void TcpSession::set_link_value() {
    addr_ = socket_.remote_endpoint().address().to_string();
    port_ = socket_.remote_endpoint().port();
    link_str_ = addr_ + ":" + std::to_string(port_);

    spdlog::info("[+] tcp link: {}:{}", addr_, port_);
}

void TcpSession::sock_error(const std::error_code &ec) {
    StaticUnit::log->daily->error(ec.message());
    spdlog::error(ec.message());
    try {
        socket_.close();
    } catch (std::exception &e) {
        spdlog::error(e.what());
        StaticUnit::log->daily->error(e.what());
    }
}

TcpSession::~TcpSession() {
    {
        std::lock_guard<std::mutex> locker(StaticUnit::tcp_session_map_mutex);
        StaticUnit::tcp_session_map->erase(link_str_);
    }
    spdlog::info("[-] tcp link: {}", link_str_);
}

void TcpSession::start() {
    do_read();
}

void TcpSession::do_read() {
    auto self(shared_from_this());
    socket_.async_read_some(asio::buffer(data_, max_length),
                            [self](std::error_code ec, std::size_t length) {
                                self->read_handler(ec, length);
                            });
}

void TcpSession::read_handler(std::error_code ec, std::size_t length) {
    if (ec) {
        sock_error(ec);
        return;
    }
    auto now = Tools::get_now();

    std::string str(data_, length);

    decoder->decode(str, data_list, left_data);

    if(!data_list.empty()) {
        for(auto &data: data_list) {
            ReceiveData receive_data(ReceiveData::TCP, now++, type_, addr_, port_, data);
            StaticUnit::data_queue->enqueue(std::move(receive_data));
        }
        StaticUnit::data_queue_wait_condition.notify_all();
        data_list.clear();
    }

    do_read();
}


void TcpSession::write(const std::string &data,unsigned int serial_num) {
    auto self(shared_from_this());
    asio::async_write(socket_, asio::buffer(data.data(), data.size()),
                      [self, serial_num](const std::error_code &ec, std::size_t) {
            if(!ec) {
                spdlog::info("write ok:{}", serial_num);
            } else {
                spdlog::info("write error!");
                self->sock_error(ec);
            }
    });
}

