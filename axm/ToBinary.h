#pragma once

#include <array>
#include <cstdint>
#include <cstdio>
#include <memory>
#include <string>
#include <variant>
#include <vector>

namespace axm {
namespace detail {
using bytes = std::vector<uint8_t>;
void __to_binary(bytes &, const bool &);
void __to_binary(bytes &, const char &);
void __to_binary(bytes &, const uint8_t &);
void __to_binary(bytes &, const uint32_t &);
void __to_binary(bytes &, const uint64_t &);
void __to_binary(bytes &, const int8_t &);
void __to_binary(bytes &, const int32_t &);
void __to_binary(bytes &, const int64_t &);
void __to_binary(bytes &, const float &);
void __to_binary(bytes &, const double &);
void __to_binary(bytes &, const std::string &);
void __var_to_binary(bytes &, const uint32_t &);
void __var_to_binary(bytes &, const int32_t &);
void __var_to_binary(bytes &, const uint64_t &);
void __var_to_binary(bytes &, const int64_t &);

template <typename T>
void __to_binary(bytes &res, const std::vector<T> &data) {
    __to_binary(res, (uint32_t)data.size());
    for (const auto &i : data) {
        __to_binary(res, i);
    }
}

template <typename T, size_t Size>
void __to_binary(bytes &res, const std::array<T, Size> &data) {
    for (const auto &i : data) {
        __to_binary(res, i);
    }
}

template <typename T>
void __to_binary(bytes &res, const std::unique_ptr<T> &data) {
    __to_binary(res, data != nullptr);
    if (data != nullptr) {
        void __to_binary(bytes &, const T &);
        __to_binary(res, *data);
    }
}

template <typename T>
bytes to_binary(const T &object) {
    bytes res;
    void __to_binary(bytes &, const T &);
    __to_binary(res, object);
    return res;
}
}  // namespace detail

template <typename T>
std::vector<uint8_t> to_binary(const T &object) {
    return detail::to_binary(object);
}

}  // namespace axm