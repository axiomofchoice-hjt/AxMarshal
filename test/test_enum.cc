#include <gtest/gtest.h>

#include "Def.h"

TEST(enum, Calc) {
    EXPECT_TRUE(Calc::Add() != Calc::Sub());
    EXPECT_TRUE(Calc::Add() == Calc::Add());
    EXPECT_TRUE(!(Calc::Add() != Calc::Add()));

    Calc a;
    EXPECT_TRUE(a == nullptr);
    EXPECT_TRUE(!(a != nullptr));
    EXPECT_TRUE(!a.is_Add());
    EXPECT_TRUE(!a.is_Sub());

    a = Calc::Add();
    EXPECT_TRUE(a != nullptr);
    EXPECT_TRUE(!(a == nullptr));
    EXPECT_TRUE(a.is_Add());
    EXPECT_TRUE(!a.is_Sub());

    Calc b = Calc::Sub();
    a = b;
    EXPECT_TRUE(a.is_Sub());
    EXPECT_TRUE(b.is_Sub());
}

TEST(enum, Result) {
    auto r = Result::Ok();
    EXPECT_TRUE(r != nullptr);
    EXPECT_TRUE(r.is_Ok());
    r = Result::Err(233);
    EXPECT_TRUE(r.is_Err());
    EXPECT_TRUE(r.get_Err() == 233);

    auto serial = axm::to_binary(r);
    for (auto i : serial) {
        printf("%u ", i);
    }
    puts("");
    auto r2 = axm::from_binary<Result>(serial);
    EXPECT_TRUE(r2.is_Err());
    EXPECT_TRUE(r2.get_Err() == 233);

    printf("%s\n", axm::to_json(Result()).c_str());
    printf("%s\n", axm::to_json(Result::Ok()).c_str());
    printf("%s\n", axm::to_json(Result::Err(233)).c_str());
}