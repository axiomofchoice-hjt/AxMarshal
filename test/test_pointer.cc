#include <gtest/gtest.h>

#include "Def.h"

TEST(pointer, general) {
    std::vector<uint8_t> bin;
    {
        std::unique_ptr<Linked> l;
        std::unique_ptr<Linked> *i = &l;
        for (auto data : {1, 2, 3, 4}) {
            *i = std::make_unique<Linked>();
            (*i)->data = data;
            i = &(*i)->next;
        }
        bin = axm::to_binary(*l);
        EXPECT_EQ(bin, (std::vector<uint8_t>{1, 0, 0, 0, 1, 2, 0, 0, 0, 1,
                                             3, 0, 0, 0, 1, 4, 0, 0, 0, 0}));
    }
    {
        std::unique_ptr<Linked> l;
        l = std::make_unique<Linked>(axm::from_binary<Linked>(bin));
        std::unique_ptr<Linked> *i = &l;
        for (auto data : {1, 2, 3, 4}) {
            EXPECT_TRUE((*i) != nullptr);
            EXPECT_EQ((*i)->data, data);
            i = &(*i)->next;
        }
        EXPECT_TRUE(*i == nullptr);
    }
    {
        std::unique_ptr<Linked> l;
        l = std::make_unique<Linked>(axm::from_binary<Linked>(bin));
        EXPECT_EQ(
            axm::to_json(*l),
            R"({"data":1,"next":{"data":2,"next":{"data":3,"next":{"data":4,"next":null}}}})");
    }
}