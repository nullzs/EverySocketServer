#ifndef EVERYSOCKETSERVER_TCP_SESSION_H
#define EVERYSOCKETSERVER_TCP_SESSION_H

#include <memory>
#include "asio.hpp"
#include "frame_decoder.h"

class TcpSession : public std::enable_shared_from_this<TcpSession>{
public:
    explicit TcpSession(asio::ip::tcp::socket socket, int type);

    ~TcpSession();

    void start();

    std::string get_link() {
        return link_str_;
    }

    void write(const std::string &data, unsigned int serial_num);

private:
    asio::ip::tcp::socket socket_;
    int type_;
    std::string addr_;
    unsigned short port_{0};
    std::string link_str_;
    std::shared_ptr<FrameDecoder> decoder;
    std::string left_data;
    std::vector<std::string> data_list;


    enum{
        max_length = 1024
    };
    char data_[max_length]{};

    void set_link_value();
    void sock_error(const std::error_code &ec);

    void do_read();

    void read_handler(std::error_code ec, size_t length);

};


#endif //EVERYSOCKETSERVER_TCP_SESSION_H
