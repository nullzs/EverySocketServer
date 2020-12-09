#include "frame_decoder_delimiter_pair.h"
#include <utility>
#include <cassert>

FrameDecoderDelimiterPair::FrameDecoderDelimiterPair(std::string delimiter_beg,
                                                     std::string delimiter_end)
        : delimiter_beg_(std::move(delimiter_beg)), delimiter_end_(std::move(delimiter_end)) {
    beg_size = delimiter_beg_.size();
    end_size = delimiter_end_.size();
    // delimiter_beg_ and delimiter_end_ shouldn't be empty.
    assert(beg_size > 0);
    assert(end_size > 0);
}

void FrameDecoderDelimiterPair::decode(std::string &source, std::vector<std::string> &data_list,
                                       std::string &left_data) {
    //merge left data last time
    if (!left_data.empty()) {
        if (check_header_complete(source)) {
            left_data.clear();
        } else {
            // std::move can clean left_data
            left_data.append(source);
            source = std::move(left_data);
        }
    }

    decode_all(source, data_list, left_data);

}

void FrameDecoderDelimiterPair::decode_all(std::string &source, std::vector<std::string> &data_list,
                                           std::string &left_data) {
    int beg_pos{0}, end_pos{-end_size};
    int source_max_idx = static_cast<int>(source.size()) - 1;

    while ((end_pos + end_size) < source_max_idx) {
        //find begin
        beg_pos = source.find(delimiter_beg_, end_pos + end_size);
        if (beg_pos == std::string::npos) {
            left_data.append(source.substr(end_pos + end_size, source_max_idx));
            break;
        }
        //find end
        end_pos = source.find(delimiter_end_, beg_pos + beg_size);
        if (end_pos == std::string::npos) {
            left_data.append(source.substr(beg_pos, source_max_idx));
            break;
        }
        //add to list
        int data_len =  end_pos + end_size -beg_pos;
        data_list.push_back(source.substr(beg_pos, data_len));
    }

    if (left_data.size() > 2048) {
        left_data.clear();
    }
}


/*
 * check_header_complete() use to filter out dirty data in "left_data"
 */
bool FrameDecoderDelimiterPair::check_header_complete(const std::string &source) {
    // if "A" is delimiter_beg_, is false that begin isn't "A"
    if (source.substr(0, beg_size) != delimiter_beg_) return false;

    /* some times (delimiter_beg_ == delimiter_end_)
     * example:
     *  source1 :"AA0011" ,source2 :"A0011"
     *  delimiter_beg_ == delimiter_end_ == "A"
     *  source1 :"AA0011" : false (the first "A" is delimiter_end_)
     *  source2 :"A0011"  : true
     * */
    if (source.substr(0, end_size + beg_size) == (delimiter_end_ + delimiter_beg_)) return false;
    return true;
}

