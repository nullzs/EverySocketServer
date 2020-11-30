#ifndef EVERY_SOCKET_SERVER_LOG_FILE_H
#define EVERY_SOCKET_SERVER_LOG_FILE_H

#include <spdlog/spdlog.h>
#include <spdlog/sinks/daily_file_sink.h>
#include <string>

//no-copy class, simple log
class LogFile {
public:
    explicit LogFile(const std::string &path="logs/daily.txt");
    virtual ~LogFile() = default;

    LogFile(const LogFile &log_file) = delete;
    LogFile operator=(const LogFile &) = delete;

    std::shared_ptr<spdlog::logger> daily;
};


#endif //EVERY_SOCKET_SERVER_LOG_FILE_H
