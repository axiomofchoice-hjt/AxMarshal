#include <gtest/gtest.h>

#include "Def.h"

#define check_binary(type, value, expect...)                    \
    do {                                                        \
        std::vector<uint8_t> bin;                               \
        axm::detail::__var_to_binary(bin, (type)value);         \
        EXPECT_EQ(bin, (std::vector<uint8_t>(expect)));         \
        type data = 0;                                          \
        std::vector<uint8_t>::const_iterator it = bin.cbegin(); \
        axm::detail::__var_from_binary(it, data);               \
        EXPECT_EQ(it - bin.cbegin(), bin.size());               \
        EXPECT_EQ((type)value, data);                           \
    } while (0)

TEST(var_ints, var_uint32) {
    check_binary(uint32_t, 0, {0});
    check_binary(uint32_t, 0b0100'0000, {0b0100'0000});
    check_binary(uint32_t, 0b1000'0000, {0b1000'0000, 1});
    check_binary(uint32_t, 0b0110'1010'1010, {0b1010'1010, 0b0000'1101});
    check_binary(uint32_t, 0xffff'ffff, {0xff, 0xff, 0xff, 0xff, 0b1111});
}

TEST(var_ints, var_int32) {
    check_binary(int32_t, 0, {0});
    check_binary(int32_t, 0b0010'0000, {0b0100'0000});
    check_binary(int32_t, 0b0100'0000, {0b1000'0000, 1});
    check_binary(int32_t, 0x7fff'ffff, {0xfe, 0xff, 0xff, 0xff, 0b1111});
    check_binary(int32_t, 0xffff'ffff, {1});
    check_binary(int32_t, 0x8000'0000, {0xff, 0xff, 0xff, 0xff, 0b1111});
    check_binary(int32_t, 0xffff'ffbf, {0b1000'0001, 1});
}

TEST(var_ints, var_uint64) {
    check_binary(uint64_t, 0, {0});
    check_binary(uint64_t, 0b0100'0000, {0b0100'0000});
    check_binary(uint64_t, 0b1000'0000, {0b1000'0000, 1});
    check_binary(uint64_t, 0b0110'1010'1010, {0b1010'1010, 0b0000'1101});
    check_binary(uint64_t, 0xffff'ffff'ffff'ffff,
                 {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff});
}

TEST(var_ints, var_int64) {
    check_binary(int64_t, 0, {0});
    check_binary(int64_t, 0b0010'0000, {0b0100'0000});
    check_binary(int64_t, 0b0100'0000, {0b1000'0000, 1});
    check_binary(int64_t, 0x7fff'ffff'ffff'ffffL,
                 {0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff});
    check_binary(int64_t, 0xffff'ffff'ffff'ffff, {1});
    check_binary(int64_t, 0x8000'0000'0000'0000,
                 {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff});
    check_binary(int64_t, 0xffff'ffff'ffff'ffbf, {0b1000'0001, 1});
}