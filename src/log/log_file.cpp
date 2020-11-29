#include "log_file.h"

LogFile::LogFile() {
    daily = spdlog::daily_logger_mt("normal-log",
                                        "logs/daily.txt", 2, 30);
}
