#ifndef EVERYSOCKETSERVER_TCP_SESSION_H
#define EVERYSOCKETSERVER_TCP_SESSION_H

#include "asio.hpp"
#include <memory>

class TcpSession : public std::enable_shared_from_this<TcpSession>{
public:
    explicit TcpSession(asio::ip::tcp::socket socket, int type)
    : socket_(std::move(socket))
    , type_(type)
    {
        set_link_value();
    }

    ~TcpSession();

    void start();

    std::string get_link() {
        return link_str_;
    }

private:
    asio::ip::tcp::socket socket_;
    int type_;
    std::string addr_;
    unsigned short port_;
    std::string link_str_;

    enum{
        max_length = 1024
    };
    char data_[max_length]{};

    void set_link_value();
    void sock_error(std::error_code &ec);

    void do_read();

    void read_handler(std::error_code ec, size_t length);
};


#endif //EVERYSOCKETSERVER_TCP_SESSION_H
