#ifndef EVERYSOCKETSERVER_DECODER_TOOLS_H
#define EVERYSOCKETSERVER_DECODER_TOOLS_H

#include "frame_decoder.h"
#include <memory>

class DecoderTools {
public:
    DecoderTools() = delete;
    static std::shared_ptr<FrameDecoder> get_decoder(int type);

    enum protocol{
        default_test = 1
    };
};


#endif //EVERYSOCKETSERVER_DECODER_TOOLS_H
