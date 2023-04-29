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
void __from_binary_le(bytes_iter &it, void *data) {
    for (size_t i = 0; i < N; i++) {
        ((uint8_t *)data)[i] = *it;
        ++it;
    }
}

template <size_t N>
void __from_binary_be(bytes_iter &it, void *data) {
    for (size_t i = N - 1; i != SIZE_MAX; i--) {
        ((uint8_t *)data)[i] = *it;
        it += 1;
    }
}

template <is_number T>
void __from_binary(bytes_iter &it, T &data) {
    if constexpr (std::endian::native == std::endian::little) {
        __from_binary_le<sizeof(T)>(it, &data);
    } else {
        __from_binary_be<sizeof(T)>(it, &data);
    }
}

template <typename Iter>
void __container_from_binary(bytes_iter &it, Iter l, Iter r) {
    for (Iter i = l; i != r; ++i) {
        __from_binary(it, *i);
    }
}

void __var_from_binary(bytes_iter &, uint32_t &);
void __var_from_binary(bytes_iter &, int32_t &);
void __var_from_binary(bytes_iter &, uint64_t &);
void __var_from_binary(bytes_iter &, int64_t &);
void __from_binary(bytes_iter &, std::string &);

template <typename T>
void __from_binary(bytes_iter &it, std::vector<T> &data) {
    uint32_t size;
    __from_binary(it, size);
    data.resize(size);
    __container_from_binary(it, data.begin(), data.end());
}

template <typename T, size_t Size>
void __from_binary(bytes_iter &it, std::array<T, Size> &data) {
    __container_from_binary(it, data.begin(), data.end());
}

template <typename T>
void __from_binary(bytes_iter &it, std::unique_ptr<T> &data) {
    bool tmp;
    __from_binary(it, tmp);
    if (tmp) {
        data = std::make_unique<T>();
        void __from_binary(bytes_iter &, T &);
        __from_binary(it, *data);
    } else {
        data = nullptr;
    }
}

template <typename T>
T from_binary(const bytes &bin) {
    T res;
    bytes_iter tmp_iter = bin.cbegin();
    void __from_binary(bytes_iter &, T &);
    __from_binary(tmp_iter, res);
    if (tmp_iter != bin.cend()) {
        printf("from_binary fail: %zd\n", tmp_iter - bin.cend());
        throw "from_binary fail";
    }
    return res;
}
}  // namespace detail

template <typename T>
T from_binary(const std::vector<uint8_t> &bin) {
    return detail::from_binary<T>(bin);
}
}  // namespace axm