#ifndef EVERYSOCKETSERVER_FRAME_DECODER_DEFAULT_H
#define EVERYSOCKETSERVER_FRAME_DECODER_DEFAULT_H

#include "frame_decoder.h"

class FrameDecoderDefault : public FrameDecoder {
public:
    FrameDecoderDefault() = default;
    ~FrameDecoderDefault() override = default;
    void decode(std::string &source, std::vector<std::string> &data_list,
                std::string &left_data) override ;
};


#endif //EVERYSOCKETSERVER_FRAME_DECODER_DEFAULT_H
