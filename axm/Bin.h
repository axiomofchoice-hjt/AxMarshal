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
using bytes_iter = std::vector<uint8_t>::const_iterator;
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

void __from_binary(bytes_iter &, bool &);
void __from_binary(bytes_iter &, char &);
void __from_binary(bytes_iter &, uint8_t &);
void __from_binary(bytes_iter &, uint32_t &);
void __from_binary(bytes_iter &, uint64_t &);
void __from_binary(bytes_iter &, int8_t &);
void __from_binary(bytes_iter &, int32_t &);
void __from_binary(bytes_iter &, int64_t &);
void __from_binary(bytes_iter &, float &);
void __from_binary(bytes_iter &, double &);
void __from_binary(bytes_iter &, std::string &);
void __var_from_binary(bytes_iter &, uint32_t &);
void __var_from_binary(bytes_iter &, int32_t &);
void __var_from_binary(bytes_iter &, uint64_t &);
void __var_from_binary(bytes_iter &, int64_t &);

template <typename T>
void __from_binary(bytes_iter &it, std::vector<T> &data) {
    uint32_t size;
    __from_binary(it, size);
    data.resize(size);
    for (auto &i : data) {
        __from_binary(it, i);
    }
}

template <typename T, size_t Size>
void __from_binary(bytes_iter &it, std::array<T, Size> &data) {
    for (auto &i : data) {
        __from_binary(it, i);
    }
}

template <typename T>
void __from_binary(bytes_iter &it, std::unique_ptr<T> &data) {
    bool tmp;
    __from_binary(it, tmp);
    if (tmp) {
        data = std::make_unique<T>();
        void __from_binary(bytes_iter &, T &data);
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