#define CATCH_CONFIG_MAIN
#include "test.h"

TEST_CASE( "Test", "[test]" ) {
    int i{0};
    REQUIRE_FALSE(i > 0);
}