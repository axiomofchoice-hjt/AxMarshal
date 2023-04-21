#include <gtest/gtest.h>

#include "Def.h"

TEST(array, general) {
    std::vector<uint8_t> bin;
    {
        Array arr;
        arr.el[0] = 10;
        arr.el[1] = 20;
        arr.el[2] = 30;
        arr.el[3] = 40;
        bin = axm::to_binary(arr);
        EXPECT_EQ(bin, (std::vector<uint8_t>{10, 0, 0, 0, 20, 0, 0, 0, 30, 0, 0,
                                             0, 40, 0, 0, 0}));
    }
    {
        Array arr;
        arr = axm::from_binary<Array>(bin);

        EXPECT_EQ(arr.el[0], 10);
        EXPECT_EQ(arr.el[1], 20);
        EXPECT_EQ(arr.el[2], 30);
        EXPECT_EQ(arr.el[3], 40);
        EXPECT_TRUE(axm::to_json(arr) == R"({"el":[10,20,30,40]})");
    }
}