#ifndef EVERYSOCKETSERVER_FRAME_DECODER_DELIMITER_PAIR_H
#define EVERYSOCKETSERVER_FRAME_DECODER_DELIMITER_PAIR_H

#include "frame_decoder.h"

class FrameDecoderDelimiterPair : public FrameDecoder {
public:
    explicit FrameDecoderDelimiterPair(std::string delimiter_beg, std::string delimiter_end);
    void decode(std::string &source, std::vector<std::string> &data_list,
                std::string &left_data) override;
private:
    std::string delimiter_beg_;
    std::string delimiter_end_;
    int beg_size{0};
    int end_size{0};

    bool check_header_complete(const std::string &source);

    void decode_all(std::string &source, std::vector<std::string> &data_list, std::string &left_data);
};


#endif //EVERYSOCKETSERVER_FRAME_DECODER_DELIMITER_PAIR_H
