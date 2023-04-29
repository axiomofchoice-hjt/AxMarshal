#include "to_binary.h"

#include <bit>
#include <cstdint>
#include <typeinfo>
#include <vector>

namespace axm {
namespace detail {
void __to_binary(bytes &res, const std::string &data) {
    res.reserve(4 + data.size());
    __to_binary(res, (uint32_t)data.size());
    __container_to_binary(res, data.cbegin(), data.cend());
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