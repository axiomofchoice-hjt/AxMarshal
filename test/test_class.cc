#include <gtest/gtest.h>

#include "Def.h"
TEST(class, general) {
    std::vector<uint8_t> bin;
    {
        User user;
        user.id = 1;
        user.name = "Tom";
        user.gender = 'M';
        user.score = 1.125f;
        user.follows.push_back(2);
        user.follows.push_back(3);
        user.follows.push_back(4);
        user.state = Result::Err(233);
        bin = axm::to_binary(user);
        EXPECT_TRUE(
            (bin == std::vector<uint8_t>{
                        1, 0,   0,  0, 3, 0, 0, 0, 84, 111, 109, 77, 0, 0,
                        0, 144, 63, 3, 0, 0, 0, 2, 0,  0,   0,   3,  0, 0,
                        0, 4,   0,  0, 0, 2, 0, 0, 0,  233, 0,   0,  0}));
    }
    {
        User user;
        user = axm::from_binary<User>(bin);
        EXPECT_TRUE(user.id == 1);
        EXPECT_TRUE(user.name == "Tom");
        EXPECT_TRUE(user.gender == 'M');
        EXPECT_TRUE(user.score == 1.125f);
        EXPECT_TRUE(user.follows.size() == 3);
        EXPECT_TRUE(user.follows[0] == 2);
        EXPECT_TRUE(user.follows[1] == 3);
        EXPECT_TRUE(user.follows[2] == 4);
        EXPECT_TRUE(user.state.is_Err());
        EXPECT_TRUE(user.state.get_Err() == 233);
        EXPECT_TRUE(user.gender == 'M');

        EXPECT_TRUE(
            axm::to_json(user) ==
            R"({"id":1,"name":"Tom","gender":"M","online":false,"score":1.125,"follows":[2,3,4],"state":{"Err":233}})");
    }
}