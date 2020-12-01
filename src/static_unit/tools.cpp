#include "tools.h"
#include <sstream>
#include <iomanip>

void Tools::convert_hex(std::string &str) {
    std::ostringstream result;
    for (unsigned char val: str) {
        result << std::uppercase << std::setw(2) << std::setfill('0') << std::hex << static_cast<unsigned short>(val);
    }
    str = std::move(result.str());

}
