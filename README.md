# AxMarshal

随手写的类似 protobuf 的工具

## 枚举类型

定义纯 enum 类型

```text
enum Calc {
    Add,
    Sub,
    Mul,
    Div,
}
```

定义携带数据的 enum 类型

```text
enum Result {
    Ok,
    Err(int),
}
```

接口：

- `Calc calc;` 定义一个空的 Calc
- `calc = Calc::Add();` 赋值为 Calc::Add
- `auto res = Result::Err(1);` 定义携带数据的 Err
- `calc == nullptr` 判断是否为空
- `calc.is_Add()` 判断是否为 Add
- `calc == other_calc` 判断两个 enum 是否相等（只比较类型）
- `res.get_Err()` 返回携带的数据（类型不安全，请先用 `is_Err()` 判断后再 `get_Err()`）

## struct

定义类

```text
struct User {
    id: int,
    name: string,
    gender: char,
    online: bool,
    score: float,
    follows: int[],
    state: Result,
}
```

编译后得到类似下面的结构

```cpp
struct User {
    int id;
    std::string name;
    char gender;
    bool online;
    float score;
    std::vector<int> follows;
    Result result;
};
```

## 变长整数

支持 4 种变长整数：`var_uint32` `var_int32` `var_uint64` `var_int64`，和普通整数的唯一区别是序列化后的长度不固定

32 位变长整数序列化后为 1 到 5 字节，64 位序列化后为 1 到 9 字节

整数绝对值越小，序列化后的字节越少

## 数组

仅支持在 struct 里声明

- `T[]` 即变长数组，编译后的类型是 `std::vector<T>`
- `T[size]`（size 为十进制数字）即定长数组，编译后的类型是 `std::array<T, size>`

```text
struct Arrays {
    vec: int[],
    arr: int[4],
}
```

## 指针

仅支持在 struct 里声明

- `T *` 即指向 T 类型的指针，编译后的类型是 `std::unique_ptr<T>`

利用指针可以实现链表如下

```text
struct Linked {
    data: int;
    next: Linked *;
}
```

## 序列化

- `axm::to_binary(object)` 得到二进制序列化的结果，返回类型 `std::vector<uint8_t>`
- `axm::from_binary<Result>(bytes)` 得到二进制反序列化的结果，参数类型 `std::vector<uint8_t>`，返回类型 `Result`
- `axm::to_json(object)` 得到 Json 序列化的结果，返回类型 `std::string`