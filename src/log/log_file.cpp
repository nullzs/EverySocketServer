#include "log_file.h"

LogFile::LogFile(const std::string &path) {
    daily = spdlog::daily_logger_mt("normal-log",
                                        path, 2, 30);
}
