#include "Bin.h"

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

void __from_binary(bytes_iter &it, bool &data) {
    __from_binary(it, (uint8_t &)data);
}
void __from_binary(bytes_iter &it, char &data) {
    __from_binary(it, (uint8_t &)data);
}
void __from_binary(bytes_iter &it, uint8_t &data) {
    data = *it;
    ++it;
}
void __from_binary(bytes_iter &it, uint32_t &data) {
    data = uint32_t(*it) | uint32_t(*(it + 1)) << 8 |
           uint32_t(*(it + 2)) << 16 | uint32_t(*(it + 3)) << 24;
    it += 4;
}
void __from_binary(bytes_iter &it, uint64_t &data) {
    data = 0;
    uint32_t tmp;
    __from_binary(it, tmp);
    data |= tmp;
    __from_binary(it, tmp);
    data |= uint64_t(tmp) << 32;
}
void __from_binary(bytes_iter &it, int8_t &data) {
    __from_binary(it, (uint8_t &)data);
}
void __from_binary(bytes_iter &it, int32_t &data) {
    __from_binary(it, (uint32_t &)data);
}
void __from_binary(bytes_iter &it, int64_t &data) {
    __from_binary(it, (uint64_t &)data);
}
void __from_binary(bytes_iter &it, float &data) {
    __from_binary(it, (uint32_t &)data);
}
void __from_binary(bytes_iter &it, double &data) {
    __from_binary(it, (uint64_t &)data);
}
void __from_binary(bytes_iter &it, std::string &data) {
    uint32_t size;
    __from_binary(it, size);
    data.resize(size);
    for (auto &i : data) {
        __from_binary(it, i);
    }
}

template <typename T>
void __var_u_from_binary(bytes_iter &it, T &data) {
    bool flag;
    uint32_t index = 0;
    data = 0;
    do {
        if (index == 8) {
            data |= (T)*it << (index * 7);
            it += 1;
            break;
        }
        flag = (*it & 0x80);
        data |= (T)(*it & 0x7f) << (index * 7);
        it += 1;
        index++;
    } while (flag);
}
void __var_from_binary(bytes_iter &it, uint32_t &data) {
    __var_u_from_binary(it, data);
}
void __var_from_binary(bytes_iter &it, int32_t &data) {
    uint32_t tmp;
    __var_u_from_binary(it, tmp);
    data = (tmp & 1 ? ~(tmp >> 1) : tmp >> 1);
}
void __var_from_binary(bytes_iter &it, uint64_t &data) {
    __var_u_from_binary(it, data);
}
void __var_from_binary(bytes_iter &it, int64_t &data) {
    uint64_t tmp;
    __var_u_from_binary(it, tmp);
    data = (tmp & 1 ? ~(tmp >> 1) : tmp >> 1);
}
}  // namespace detail
}  // namespace axm