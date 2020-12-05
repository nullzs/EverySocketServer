#include "tools.h"
#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include <sstream>
#include <iomanip>

void Tools::convert_hex(std::string &str) {
    std::ostringstream result;
    for (unsigned char val: str) {
        result << std::uppercase << std::setw(2) << std::setfill('0') << std::hex << static_cast<unsigned short>(val);
    }
    str = std::move(result.str());

}

void Tools::serialize_receive(std::string &ret, const ReceiveData &receive_data) {
    rapidjson::StringBuffer buffer;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);

    writer.StartObject();

    writer.Key("type");
    writer.Int(receive_data.type);

    writer.Key("addr");
    writer.String(receive_data.addr.data());

    writer.Key("port");
    writer.Uint(receive_data.port);

    writer.Key("sock_type");
    writer.Int(receive_data.sock_type);

    writer.Key("data");
    writer.String(receive_data.data.data());

    writer.Key("timestamp");
    writer.Int64(receive_data.timestamp);

    writer.EndObject();

    ret = buffer.GetString();
}
