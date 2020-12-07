#include "frame_decoder_default.h"

void FrameDecoderDefault::decode(std::string &source, std::vector<std::string> &data_list,
                                 std::string &left_data) {
    data_list.push_back(std::move(source));
}
