#include "decoder_tools.h"
#include "decoder/frame_decoder_delimiter_pair.h"
#include "decoder/frame_decoder_default.h"

std::shared_ptr<FrameDecoder> DecoderTools::get_decoder(int type) {
    if (type == protocol::default_test) {
        std::string beg_str(1, 0x7e);
        std::string end_str(1, 0x7e);
        return std::make_shared<FrameDecoderDelimiterPair>(beg_str, end_str);
    }

    return std::make_shared<FrameDecoderDefault>();
}