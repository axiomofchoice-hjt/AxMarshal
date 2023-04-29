#include "to_binary.h"

#include <bit>
#include <cstdint>
#include <typeinfo>
#include <vector>

namespace axm {
namespace detail {
void __to_binary(bytes &res, const bool &data) {
    __to_binary(res, (uint8_t)data);
}
void __to_binary(bytes &res, const char &data) {
    __to_binary(res, (uint8_t)data);
}
void __to_binary(bytes &res, const uint8_t &data) { res.push_back(data); }
void __to_binary(bytes &res, const uint32_t &data) {
    res.reserve(4);
    res.push_back((uint8_t)data);
    res.push_back((uint8_t)(data >> 8));
    res.push_back((uint8_t)(data >> 16));
    res.push_back((uint8_t)(data >> 24));
}
void __to_binary(bytes &res, const uint64_t &data) {
    res.reserve(8);
    __to_binary(res, (uint32_t)data);
    __to_binary(res, (uint32_t)(data >> 32));
}
void __to_binary(bytes &res, const int8_t &data) {
    __to_binary(res, (uint8_t)data);
}
void __to_binary(bytes &res, const int32_t &data) {
    __to_binary(res, (uint32_t)data);
}
void __to_binary(bytes &res, const int64_t &data) {
    __to_binary(res, (uint64_t)data);
}
void __to_binary(bytes &res, const float &data) {
    __to_binary(res, std::bit_cast<uint32_t>(data));
}
void __to_binary(bytes &res, const double &data) {
    __to_binary(res, std::bit_cast<uint64_t>(data));
}
void __to_binary(bytes &res, const std::string &data) {
    res.reserve(4 + data.size());
    __to_binary(res, (uint32_t)data.size());
    for (const auto &i : data) {
        __to_binary(res, i);
    }
}
template <typename T>
void __var_u_to_binary(bytes &res, T data) {
    bool flag;
    uint32_t index = 0;
    do {
        if (index == 8) {
            res.push_back(data);
            break;
        }
        flag = (data >= 0x80);
        res.push_back((flag ? 0x80 : 0) | (data & 0x7f));
        data >>= 7;
        index++;
    } while (flag);
}
void __var_to_binary(bytes &res, const uint32_t &data) {
    __var_u_to_binary(res, data);
}
void __var_to_binary(bytes &res, const int32_t &data) {
    __var_u_to_binary(
        res, (data >= 0 ? (uint32_t)data << 1 : ~(uint32_t)data << 1 | 1));
}
void __var_to_binary(bytes &res, const uint64_t &data) {
    __var_u_to_binary(res, data);
}
void __var_to_binary(bytes &res, const int64_t &data) {
    __var_u_to_binary(
        res, (data >= 0 ? (uint64_t)data << 1 : ~(uint64_t)data << 1 | 1));
}

}  // namespace detail
}  // namespace axm