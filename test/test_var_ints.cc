#include <gtest/gtest.h>

#include "Def.h"
TEST(var_ints, var_uint32) {
    {
        std::vector<uint8_t> bin;
        VarUint32 t;
        t.value = 0;
        bin = axm::to_binary(t);
        EXPECT_TRUE(bin == std::vector<uint8_t>{0});
        t.value = 1;
        bin = axm::to_binary(t);
        EXPECT_TRUE(bin == std::vector<uint8_t>{1});
        t.value = 0b110'1010'1010;
        bin = axm::to_binary(t);
        EXPECT_TRUE((bin == std::vector<uint8_t>{0b1010'1010, 0b1101}));
        t.value = 0xffffffff;
        bin = axm::to_binary(t);
        EXPECT_TRUE(
            (bin == std::vector<uint8_t>{0xff, 0xff, 0xff, 0xff, 0b1111}));
    }
}