#pragma once

#include <array>
#include <cstdio>
#include <memory>
#include <string>
#include <variant>

#include "defines.h"

namespace axm {
namespace detail {
template <size_t N>
void __to_binary_le(bytes &res, const void *data) {
    res.reserve(N);
    for (size_t i = 0; i < N; i++) {
        res.push_back(((const uint8_t *)data)[i]);
    }
}

template <size_t N>
void __to_binary_be(bytes &res, const void *data) {
    res.reserve(N);
    for (size_t i = N - 1; i != SIZE_MAX; i--) {
        res.push_back(((const uint8_t *)data)[i]);
    }
}

template <is_number T>
void __to_binary(bytes &res, const T &data) {
    if constexpr (std::endian::native == std::endian::little) {
        __to_binary_le<sizeof(T)>(res, &data);
    } else {
        __to_binary_be<sizeof(T)>(res, &data);
    }
}

void __to_binary(bytes &, const std::string &);
void __var_to_binary(bytes &, const uint32_t &);
void __var_to_binary(bytes &, const int32_t &);
void __var_to_binary(bytes &, const uint64_t &);
void __var_to_binary(bytes &, const int64_t &);

template <typename Iter>
void __container_to_binary(bytes &res, Iter l, Iter r) {
    for (Iter i = l; i != r; ++i) {
        __to_binary(res, *i);
    }
}

template <typename T>
void __to_binary(bytes &res, const std::vector<T> &data) {
    __to_binary(res, (uint32_t)data.size());
    __container_to_binary(res, data.cbegin(), data.cend());
}

template <typename T, size_t Size>
void __to_binary(bytes &res, const std::array<T, Size> &data) {
    __container_to_binary(res, data.cbegin(), data.cend());
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