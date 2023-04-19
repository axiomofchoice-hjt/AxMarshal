#include <cstdio>
#include <utility>

#include "Def.h"

#define assert(state)                                        \
    do {                                                     \
        if (!(state)) {                                      \
            printf("assert fail: line=%d\n", __LINE__);      \
            throw;                                           \
        } else {                                             \
            if (0) printf("assert ok: line=%d\n", __LINE__); \
        }                                                    \
    } while (false)

void enum_test() {
    assert(Calc::Add() != Calc::Sub());
    assert(Calc::Add() == Calc::Add());
    assert(!(Calc::Add() != Calc::Add()));
    printf("sizeof SEnum = %zu\n", sizeof(Calc));
    printf("sizeof CEnum = %zu\n", sizeof(Result));

    Calc a;
    assert(a == nullptr);
    assert(!(a != nullptr));
    assert(!a.is_Add());
    assert(!a.is_Sub());

    a = Calc::Add();
    assert(a != nullptr);
    assert(!(a == nullptr));
    assert(a.is_Add());
    assert(!a.is_Sub());

    Calc b = Calc::Sub();
    a = b;
    assert(a.is_Sub());
    assert(b.is_Sub());

    auto r = Result::Ok();
    assert(r != nullptr);
    assert(r.is_Ok());
    r = Result::Err(233);
    assert(r.is_Err());
    assert(r.get_Err() == 233);

    auto serial = axm::to_binary(r);
    for (auto i : serial) {
        printf("%u ", i);
    }
    puts("");
    auto r2 = axm::from_binary<Result>(serial);
    assert(r2.is_Err());
    assert(r2.get_Err() == 233);

    printf("%s\n", axm::to_json(Result()).c_str());
    printf("%s\n", axm::to_json(Result::Ok()).c_str());
    printf("%s\n", axm::to_json(Result::Err(233)).c_str());
}

void class_test() {
    std::vector<uint8_t> bin;
    {
        User user;
        user.id = 1;
        user.name = "Tom";
        user.gender = 'M';
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
        User user = axm::from_binary<User>(bin);
        assert(user.id == 1);
        assert(user.follows.size() == 3);
        assert(user.follows[0] == 2);
        assert(user.follows[1] == 3);
        assert(user.follows[2] == 4);
        assert(user.state.is_Err());
        assert(user.state.get_Err() == 233);
        assert(user.gender == 'M');

        printf("%s\n", axm::to_json(user).c_str());
    }
}

int main() {
    try {
        enum_test();
        class_test();
    } catch (const char* error) {
        printf("error: %s\n", error);
        return 1;
    }
    return 0;
}