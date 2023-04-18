#pragma once

#include <cstdint>
#include <cstdio>
#include <string>
#include <variant>
#include <vector>

namespace axm {
namespace detail {
using bytes = std::vector<uint8_t>;
using bytes_iter = std::vector<uint8_t>::const_iterator;
void __to_binary(bytes &res, const uint8_t &data);
void __to_binary(bytes &res, const uint32_t &data);
void __to_binary(bytes &res, const uint64_t &data);
void __to_binary(bytes &res, const int8_t &data);
void __to_binary(bytes &res, const char &data);
void __to_binary(bytes &res, const int32_t &data);
void __to_binary(bytes &res, const int64_t &data);
void __to_binary(bytes &res, const float &data);
void __to_binary(bytes &res, const double &data);
void __to_binary(bytes &res, const std::string &data);
template <typename T>
void __to_binary(bytes &res, const std::vector<T> &data) {
    __to_binary(res, (uint32_t)data.size());
    for (const auto &i : data) {
        __to_binary(res, i);
    }
}
template <typename T>
bytes to_binary(const T &object) {
    bytes res;
    void __to_binary(bytes &, const T &);
    __to_binary(res, object);
    return res;
}

void __from_binary(bytes_iter &it, uint8_t &data);
void __from_binary(bytes_iter &it, uint32_t &data);
void __from_binary(bytes_iter &it, uint64_t &data);
void __from_binary(bytes_iter &it, int8_t &data);
void __from_binary(bytes_iter &it, char &data);
void __from_binary(bytes_iter &it, int32_t &data);
void __from_binary(bytes_iter &it, int64_t &data);
void __from_binary(bytes_iter &it, float &data);
void __from_binary(bytes_iter &it, double &data);
void __from_binary(bytes_iter &it, std::string &data);
template <typename T>
void __from_binary(bytes_iter &it, std::vector<T> &data) {
    uint32_t size;
    __from_binary(it, size);
    data.resize(size);
    for (auto &i : data) {
        __from_binary(it, i);
    }
}
template <typename T>
T from_binary(const bytes &bin) {
    T res;
    bytes_iter tmp_iter = bin.cbegin();
    void __from_binary(bytes_iter &, T &);
    __from_binary(tmp_iter, res);
    if (tmp_iter != bin.cend()) {
        printf("%zd\n", tmp_iter - bin.cend());
        throw "from_binary fail";
    }
    return res;
}
}  // namespace detail

template <typename T>
std::vector<uint8_t> to_binary(const T &object) {
    return detail::to_binary(object);
}

template <typename T>
T from_binary(const std::vector<uint8_t> &bin) {
    return detail::from_binary<T>(bin);
}
}  // namespace axm