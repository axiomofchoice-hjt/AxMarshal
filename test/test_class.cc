#include <gtest/gtest.h>

#include "Def.h"
TEST(class, bin) {
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
        for (auto i : bin) {
            printf("%u ", i);
        }
        puts("");
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

        printf("%s\n", axm::to_json(user).c_str());
    }
}