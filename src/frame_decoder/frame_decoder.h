#ifndef EVERYSOCKETSERVER_FRAME_DECODER_H
#define EVERYSOCKETSERVER_FRAME_DECODER_H

#include <string>
#include <vector>

class FrameDecoder {
public:
    FrameDecoder() = default;

    virtual ~FrameDecoder() = default;

    virtual void decode(std::string &source, std::vector<std::string> &data_list,
                        std::string &left_data) = 0;
};


#endif //EVERYSOCKETSERVER_FRAME_DECODER_H
