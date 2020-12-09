#include "test.h"
#include "decoder/frame_decoder_delimiter_pair.h"
#include "tools.h"

TEST_CASE("Decoder", "[delimiter_pair]") {
    std::string begin(1, 0x7e);
    std::string end(1, 0x7e);
    auto decoder = std::make_shared<FrameDecoderDelimiterPair>(begin, end);
    std::string test_str;
    Tools::convert_hex_to_str(test_str);
    std::vector<std::string> list;
    std::string left;
    SECTION( "delimiter_pair_base" ) {
        test_str ="7E11111111117E7E22222222227E";
        Tools::convert_hex_to_str(test_str);
        decoder->decode(test_str, list, left);

        std::string ret1{"7E11111111117E"};
        std::string ret2{"7E22222222227E"};
        Tools::convert_hex_to_str(ret1);
        Tools::convert_hex_to_str(ret2);

        REQUIRE(list.size() == 2);
        REQUIRE(list.at(0) == ret1);
        REQUIRE(list.at(1) == ret2);
        REQUIRE(left.empty() == true);
        list.clear();
        left.clear();
    }

    SECTION( "delimiter_pair_dirty_data" ) {
        test_str ="3456787E11111111117E7E22222222227E";
        Tools::convert_hex_to_str(test_str);
        decoder->decode(test_str, list, left);

        std::string ret1{"7E11111111117E"};
        std::string ret2{"7E22222222227E"};

        REQUIRE(list.size() == 2);
        REQUIRE(Tools::get_convert_hex(list.at(0)) == ret1);
        REQUIRE(Tools::get_convert_hex(list.at(1)) == ret2);
        REQUIRE(left.empty() == true);
        list.clear();
        left.clear();
    }


}